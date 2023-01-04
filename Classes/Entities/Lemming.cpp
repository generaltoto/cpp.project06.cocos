#include "Lemming.h"

int Lemming::m_nextId = 1;

Lemming* Lemming::create(const char* filePath, cocos2d::Vec2 pos)
{
	auto* _ret = new (std::nothrow) Lemming();
	if (_ret && _ret->init())
	{
		_ret->autorelease();
		_ret->setAnchorPoint({ 0,0 });
		_ret->setPosition(pos.x, pos.y);
		_ret->m_id = m_nextId++;
		_ret->setName(lemming_name_template + std::to_string(_ret->m_id));
		_ret->m_currentState = SPAWNING;
		_ret->m_currentAcceleration = 1;
		_ret->m_lemmingSpriteSize = { 21, 21 };

		_ret->CreateSpriteFrames(_ret, filePath);

		cocos2d::PhysicsBody* _lemmingPhysicBody = cocos2d::PhysicsBody::createBox(
			cocos2d::Size(_ret->m_pIdleSpriteFrame->getContentSize() * spriteScale),
			cocos2d::PhysicsMaterial(cocos2d::PHYSICSBODY_MATERIAL_DEFAULT)
		);
		_lemmingPhysicBody->setRotationEnable(false);
		_lemmingPhysicBody->setDynamic(true);
		_lemmingPhysicBody->setGravityEnable(true);
		_lemmingPhysicBody->getShape(0)->setRestitution(0);
		_lemmingPhysicBody->setVelocity({ 0,0 });
		_lemmingPhysicBody->setLinearDamping(0);
		_lemmingPhysicBody->setAngularDamping(0);
		_lemmingPhysicBody->setCategoryBitmask(lemming_collision_mask_id);
		_lemmingPhysicBody->setCollisionBitmask(window_collision_mask_id);
		_lemmingPhysicBody->setContactTestBitmask(test_collision_mask_id);
		_lemmingPhysicBody->setName(lemming_name_template + std::to_string(_ret->m_id));
		_ret->setPhysicsBody(_lemmingPhysicBody);
	}
	else CC_SAFE_DELETE(_ret);
	return _ret;
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
	const cocos2d::Vec2 _velocity = getPhysicsBody()->getVelocity();

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

void Lemming::CreateSpriteFrames(Lemming* _ret, const char* filePath)
{
	// Create idle Sprite Frame
	_ret->m_pIdleSpriteFrame = cocos2d::Sprite::create(
		filePath,
		cocos2d::Rect(23, 46, _ret->m_lemmingSpriteSize.x, _ret->m_lemmingSpriteSize.y)
	);
	assert(_ret->m_pIdleSpriteFrame);
	_ret->m_pIdleSpriteFrame->setScale(spriteScale);
	_ret->addChild(_ret->m_pIdleSpriteFrame);

	// Create falling sprite frame
	_ret->m_pFallingSpriteFrames = CreateSpriteFramesFromImage({ 23,137 }, 2, filePath);
	_ret->m_pWalkingSpriteFrames = CreateSpriteFramesFromImage({ 22.80,90.5 }, 4, filePath);
	_ret->m_pMiningSpriteFrames = CreateSpriteFramesFromImage({ 23,210 }, 4, filePath);
}

cocos2d::Vector<cocos2d::SpriteFrame*> Lemming::CreateSpriteFramesFromImage(cocos2d::Vec2 startingPoint, int nbFrames, const char* filePath)
{
	cocos2d::Vector<cocos2d::SpriteFrame*> _frames;
	for (int i = 1; i <= nbFrames; i++)
	{
		cocos2d::SpriteFrame* _frame = cocos2d::SpriteFrame::create(
			filePath,
			cocos2d::Rect(startingPoint.x * i, startingPoint.y, lemmingSpriteSize, lemmingSpriteSize)
		);
		assert(_frame);
		_frames.pushBack(_frame);
	}
	return _frames;
}

void Lemming::RunWithAnimation(const cocos2d::Vector<cocos2d::SpriteFrame*>& frames, bool isFlipped)
{
	cocos2d::Animation* _animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1f);
	cocos2d::Animate* _animate = cocos2d::Animate::create(_animation);

	cocos2d::Sprite* _sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
	_sprite->setScale(spriteScale);
	_sprite->setFlippedX(isFlipped);
	addChild(_sprite);
	_sprite->runAction(cocos2d::RepeatForever::create(_animate));
}
