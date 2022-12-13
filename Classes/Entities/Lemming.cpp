#include "Lemming.h"

Lemming* Lemming::create(const char* filePath, cocos2d::Vec2 pos)
{
	auto* _ret = new (std::nothrow) Lemming();
	if (_ret && _ret->init())
	{
		_ret->autorelease();
		_ret->sprite = cocos2d::Sprite::create(filePath);
		if (_ret->sprite == nullptr) throw ERROR_BAD_PATHNAME;

		_ret->sprite->setScale(0.5f);
		_ret->sprite->setAnchorPoint({ 0,0 });
		_ret->sprite->setPosition(pos.x, pos.y);

		const auto _lemmingPhysicBody = cocos2d::PhysicsBody::createBox(
			cocos2d::Size(_ret->sprite->getContentSize()),
			cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f)
		);
		_lemmingPhysicBody->setDynamic(true);
		_lemmingPhysicBody->setGravityEnable(true);
		_lemmingPhysicBody->getShape(0)->setRestitution(0);
		//_lemmingPhysicBody->setVelocity({ 75,0 });
		_lemmingPhysicBody->setCategoryBitmask(lemming_collision_mask_id);
		_lemmingPhysicBody->setCollisionBitmask(window_collision_mask_id);
		_ret->sprite->addComponent(_lemmingPhysicBody);
	}
	else CC_SAFE_DELETE(_ret);
	return _ret;
}

bool Lemming::init()
{
	if (!Node::init()) return false;
	return true;
}

void Lemming::updateVelocity(float delta, cocos2d::Size vSize, cocos2d::Vec2 vOrigin, float platformHeight)
{




	//const cocos2d::Vec2 _objPos = this->sprite->getPosition();
	//const cocos2d::Vec2 _objSize = this->sprite->getBoundingBox().size;

	//const auto _spritePhysicalBody = this->sprite->getPhysicsBody();
	//const auto _curVelocity = _spritePhysicalBody->getVelocity();

	//// Change direction when hitting a wall 
	//if ((_objPos.x + _objSize.x) >= vSize.width || _objPos.x <= vOrigin.x)
	//{
	//	_spritePhysicalBody->setVelocity({_curVelocity.x * -1, _curVelocity.y});
	//}

	//// Change acceleration to null if lemming is in the falling (vertical fall)
	//if (_objPos.y > platformHeight)
	//{
	//	_spritePhysicalBody->setVelocity({0, 0});
	//}
	//else
	//{
	//	_spritePhysicalBody->setVelocity({_curVelocity.x, 0});
	//}
}
