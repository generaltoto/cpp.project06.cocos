#include "Lemming.h"

int Lemming::nextId = 1;

Lemming* Lemming::create(const char* filePath, cocos2d::Vec2 pos)
{
	auto* _ret = new (std::nothrow) Lemming();
	if (_ret && _ret->init())
	{
		_ret->autorelease();
		_ret->setScale(0.5f);
		_ret->setAnchorPoint({ 0,0 });
		_ret->setPosition(pos.x, pos.y);
		_ret->id = nextId++;
		_ret->setName(lemming_name_template + std::to_string(_ret->id));
		_ret->currentState = SPAWNING;

		const auto _sp = cocos2d::Sprite::create(filePath);
		if (_sp == nullptr) throw ERROR_BAD_PATHNAME;
		_ret->addChild(_sp);

		const auto _lemmingPhysicBody = cocos2d::PhysicsBody::createBox(
			cocos2d::Size(_sp->getContentSize()),
			cocos2d::PhysicsMaterial(1.f, 0.f, 0.5)
		);
		_lemmingPhysicBody->setDynamic(true);
		_lemmingPhysicBody->setGravityEnable(true);
		_lemmingPhysicBody->setVelocity({ 0,0 });
		_lemmingPhysicBody->setCategoryBitmask(lemming_collision_mask_id);
		_lemmingPhysicBody->setCollisionBitmask(window_collision_mask_id);
		_lemmingPhysicBody->setContactTestBitmask(test_collision_mask_id);
		_lemmingPhysicBody->getShape(0)->getBody()->setName(lemming_name_template + std::to_string(_ret->id));
		_ret->addComponent(_lemmingPhysicBody);
	}
	else CC_SAFE_DELETE(_ret);
	return _ret;
}

bool Lemming::init()
{
	if (!Node::init()) return false;
	return true;
}

void Lemming::updateForces(float delta, float platformHeight)
{
	const cocos2d::Vec2 _objPos = this->getPosition();

	const auto _physicalBody = this->getPhysicsBody();
	const auto _curVelocity = _physicalBody->getVelocity();

	if (roundFloat(_curVelocity.y) == 0)
	{
		_physicalBody->setVelocity({ this->lemmingVelocity,0 });
		this->currentState = WALKING;
	}
	else
	{
		_physicalBody->setVelocity({ 0,_curVelocity.y });
		this->currentState = FALLING;
	}
}
