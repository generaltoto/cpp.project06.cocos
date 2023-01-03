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
		_lemmingPhysicBody->setDynamic(true);
		_lemmingPhysicBody->setGravityEnable(true);
		_lemmingPhysicBody->getShape(0)->setRestitution(0);
		_lemmingPhysicBody->setVelocity({ 0,0 });
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
	switch (m_currentState)
	{
	case FALLING:
		RunWithAnimation(m_pFallingSpriteFrames);
		break;

	case WALKING:
		RunWithAnimation(m_pWalkingSpriteFrames);
		break;

	default:
		break;
	}
}

void Lemming::checkIfFalling()
{
	const cocos2d::Vec2 _curVelocity = this->getPhysicsBody()->getVelocity();
	if (!isFloatNull(_curVelocity.y) && m_currentState != FALLING)
	{
		m_currentState = FALLING;
		getPhysicsBody()->setVelocity({ 0, _curVelocity.y });
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
	_ret->m_pIdleSpriteFrame->setTag(111);
	_ret->addChild(_ret->m_pIdleSpriteFrame);

	// Create falling sprite frame
	_ret->m_pFallingSpriteFrames = CreateSpriteFramesFromImage({ 23,144 }, 2, filePath);
	_ret->m_pWalkingSpriteFrames = CreateSpriteFramesFromImage({ 23,92 }, 4, filePath);
	_ret->m_pMiningSpriteFrames = CreateSpriteFramesFromImage({ 23,210 }, 4, filePath);
}

cocos2d::Vector<cocos2d::SpriteFrame*> Lemming::CreateSpriteFramesFromImage(cocos2d::Vec2 startingPoint, int nbFrames, const char* filePath)
{
	cocos2d::Vector<cocos2d::SpriteFrame*> _frames;
	for (int i = 0; i < nbFrames; i++)
	{
		auto _frame = cocos2d::SpriteFrame::create(
			filePath,
			cocos2d::Rect(startingPoint.x * i, startingPoint.y, lemmingSpriteSize, lemmingSpriteSize)
		);
		assert(_frame);
		_frames.pushBack(_frame);
	}
	return _frames;
}

void Lemming::RunWithAnimation(const cocos2d::Vector<cocos2d::SpriteFrame*>& frames)
{
	removeAllChildrenWithCleanup(true);
	cocos2d::Animation* _animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1f);
	cocos2d::Animate* _animate = cocos2d::Animate::create(_animation);

	cocos2d::Sprite* _sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
	_sprite->setScale(spriteScale);
	addChild(_sprite);
	_sprite->runAction(cocos2d::RepeatForever::create(_animate));
}
