#include "Lemming.h"

int Lemming::m_nextId = 1;

Lemming* Lemming::create(const char* filePath, Vec2 pos)
{
	auto* _ret = new (std::nothrow) Lemming();
	if (_ret && _ret->init())
	{
		_ret->autorelease();
		_ret->setAnchorPoint({ 0,0 });
		_ret->setPosition(pos.x, pos.y);
		_ret->m_id = m_nextId++;
		_ret->m_currentState = SPAWNING;
		_ret->m_actionState = CHILLING;
		_ret->m_currentAcceleration = 1;
		_ret->m_lemmingSpriteSize = { 21, 21 };

		_ret->CreateSpriteFrames(_ret, filePath);

		PhysicsBody* _lemmingPhysicBody = PhysicsBody::createBox(
			Size(_ret->m_pIdleSpriteFrame->getContentSize() * spriteScale),
			PhysicsMaterial(PHYSICSBODY_MATERIAL_DEFAULT)
		);
		_lemmingPhysicBody->setRotationEnable(false);
		_lemmingPhysicBody->setDynamic(true);
		_lemmingPhysicBody->setGravityEnable(true);
		_lemmingPhysicBody->getShape(0)->setRestitution(0);
		_lemmingPhysicBody->setVelocity({ 0,0 });
		_lemmingPhysicBody->setCollisionBitmask(collider_mask_id);
		_ret->setPhysicsBody(_lemmingPhysicBody);
	}
	else CC_SAFE_DELETE(_ret);
	return _ret;
}

void Lemming::UpdateActionState(LemmingActionState action)
{
	// Cancel action and go back to chilling mode
	if (m_actionState == action)
	{
		ReturnToDefaultState();
		return;
	}

	if((action == BLOCKING || action == MINING) && isFloatNull(getPhysicsBody()->getVelocity().y))
		m_actionState = action;
}

void Lemming::DoAction()
{
	switch (m_actionState)
	{
	case BLOCKING:
		// TODO Clean animation and sprite
		Block();
		// TODO Run with animation
		break;
	case MINING:
	case BUILDING:
	case JUMPING:
	case EXPLODING:
	case CHILLING:
		break;
	}
}

bool Lemming::init()
{
	if (!Node::init()) return false;
	return true;
}

void Lemming::update(float delta)
{
	Node::update(delta);

	UpdateMovementStateAndAnimation();

	Move();

	DoAction();
}

void Lemming::Move() const
{
	switch (m_currentState)
	{
	case FALLING:
		getPhysicsBody()->setVelocity({ 0, getPhysicsBody()->getVelocity().y });
		break;
	case WALKING_LEFT:
		getPhysicsBody()->setVelocity({ -m_lemmingVelocity, 0 });
		break;
	case WALKING_RIGHT:
		getPhysicsBody()->setVelocity({ m_lemmingVelocity, 0 });
		break;
	default:
		getPhysicsBody()->setVelocity({ getPhysicsBody()->getVelocity().x, getPhysicsBody()->getVelocity().y });
		break;
	}
}

void Lemming::UpdateMovementStateAndAnimation()
{
	const Vec2 _velocity = getPhysicsBody()->getVelocity();

	// Check if the lemming is stuck in a wall 
	if (isFloatNull(_velocity.x) && isFloatNull(_velocity.y))
	{
		removeAllChildrenWithCleanup(true);
		if (m_currentState == WALKING_RIGHT)
		{
			m_currentState = WALKING_LEFT;
			RunWithAnimation(m_pWalkingSpriteFrames, true);
		}
		else if (m_currentState == WALKING_LEFT)
		{
			m_currentState = WALKING_RIGHT;
			RunWithAnimation(m_pWalkingSpriteFrames, false);
		}
	}

	// Check if lemming stopped falling and is on the ground
	if (isFloatNull(_velocity.y) && m_currentState == FALLING)
	{
		removeAllChildrenWithCleanup(true);
		m_currentState = WALKING_RIGHT;
		RunWithAnimation(m_pWalkingSpriteFrames, false);
	}

	// Check if the lemming started to fall
	if (!isFloatNull(_velocity.y) && m_currentState != FALLING)
	{
		removeAllChildrenWithCleanup(true);
		m_currentState = FALLING;
		RunWithAnimation(m_pFallingSpriteFrames, false);
	}
}

void Lemming::CreateSpriteFrames(Lemming* _l, const char* filePath)
{
	// Create idle Sprite Frame
	_l->m_pIdleSpriteFrame = Sprite::create(
		filePath,
		Rect(23, 46, _l->m_lemmingSpriteSize.x, _l->m_lemmingSpriteSize.y)
	);
	assert(_l->m_pIdleSpriteFrame);
	_l->m_pIdleSpriteFrame->setScale(spriteScale);
	_l->addChild(_l->m_pIdleSpriteFrame);

	// Create falling sprite frame
	_l->m_pFallingSpriteFrames = CreateSpriteFramesFromImage({ 23,137 }, 2, filePath);
	_l->m_pWalkingSpriteFrames = CreateSpriteFramesFromImage({ 22.80,90.5 }, 4, filePath);
	_l->m_pMiningSpriteFrames = CreateSpriteFramesFromImage({ 23,210 }, 4, filePath);
}

Vector<SpriteFrame*> Lemming::CreateSpriteFramesFromImage(Vec2 startingPoint, int nbFrames, const char* filePath)
{
	Vector<SpriteFrame*> _frames;
	for (int i = 1; i <= nbFrames; i++)
	{
		SpriteFrame* _frame = SpriteFrame::create(
			filePath,
			Rect(startingPoint.x * i, startingPoint.y, lemmingSpriteSize, lemmingSpriteSize)
		);
		assert(_frame);
		_frames.pushBack(_frame);
	}
	return _frames;
}

void Lemming::RunWithAnimation(const Vector<SpriteFrame*>& frames, bool isFlipped)
{
	Animation* _animation = Animation::createWithSpriteFrames(frames, 0.1f);
	Animate* _animate = Animate::create(_animation);

	Sprite* _sprite = Sprite::createWithSpriteFrame(frames.front());
	_sprite->setScale(spriteScale);
	_sprite->setFlippedX(isFlipped);
	addChild(_sprite);
	_sprite->runAction(RepeatForever::create(_animate));
}

void Lemming::Block()
{
	PhysicsBody* _body = getPhysicsBody();
	_body->setVelocity({0,0});
	_body->addMass(3000);
}

void Lemming::ReturnToDefaultState()
{
	PhysicsBody* _body = getPhysicsBody();
	m_actionState = CHILLING;
	_body->addMass(-2700);
}
