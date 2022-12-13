#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    const auto _sceneWithPhysics = cocos2d::Scene::createWithPhysics();
    _sceneWithPhysics->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);

    const auto _layerWithPhysics = MainScene::create();
    _sceneWithPhysics->addChild(_layerWithPhysics);

    return _sceneWithPhysics;
}

bool MainScene::init()
{
    if ( !Layer::init() ) return false;

    this->visibleSize = Director::getInstance()->getVisibleSize();

    this->scheduleUpdate();

    return true;
}

void MainScene::onEnter()
{
    cocos2d::Layer::onEnter();
    const Vec2 _middleScreen = {visibleSize.width / 2, visibleSize.height / 2};
    for (int i=0; i<3; i++) this->addLemming(_middleScreen.x + (60.f * i), _middleScreen.y);
	this->addWindowsEdgesCollider();
}

void MainScene::update(float delta)
{
    Node::update(delta);

    for(auto &spLemming : this->lemmings)
    {
	    const Vec2 _objPos = spLemming.sprite->getPosition();
		const Vec2 _objSize = spLemming.sprite->getContentSize();

        // Change direction when hitting a wall 
		if ((_objPos.x + _objSize.x) >= this->visibleSize.width || _objPos.x <= 0) spLemming.lemmingAcceleration *= -1;

        // Change acceleration to null if lemming is in the air (vertical fall)
        //if (_objPos.y > 0) this->lemmingAcceleration *= 0;

		const float _movementDelta = spLemming.lemmingVelocity * delta;
		const float _newObjPosX = _objPos.x + (_movementDelta * spLemming.lemmingAcceleration);

		spLemming.sprite->setPositionX(_newObjPosX);
    }
}

void MainScene::addWindowsEdgesCollider()
{
    const auto _body = cocos2d::PhysicsBody::createEdgeBox(visibleSize, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT,1);
    _body->setCategoryBitmask(windowCollisionMaskId);
    _body->setCollisionBitmask(lemmingCollisionMaskId);

    const auto _edgeShape = cocos2d::Node::create();
    _edgeShape->setPhysicsBody(_body);
    _edgeShape->setPosition(visibleSize.width / 2, visibleSize.height / 1.7f);
    this->addChild(_edgeShape);
}

void MainScene::addLemming(float positionX, float positionY)
{
    Lemming _l;
    _l.sprite = Sprite::create("HelloWorld.png");
    if (_l.sprite == nullptr) throw ERROR_BAD_PATHNAME;

    _l.sprite->setScale(0.5f);
    _l.sprite->setPosition(positionX, positionY);
    this->addChild(_l.sprite);

    const auto _lemmingPhysicBody = cocos2d::PhysicsBody::createBox(
        cocos2d::Size(_l.sprite->getContentSize()),
        cocos2d::PhysicsMaterial(0.1f,1.0f,0.0f)
    );
    _lemmingPhysicBody->setDynamic(true);
    _lemmingPhysicBody->setGravityEnable(true);
    _lemmingPhysicBody->setCategoryBitmask(lemmingCollisionMaskId);
    _lemmingPhysicBody->setCollisionBitmask(windowCollisionMaskId);
	_l.sprite->addComponent(_lemmingPhysicBody);

    this->lemmings.push_back(_l);
}
