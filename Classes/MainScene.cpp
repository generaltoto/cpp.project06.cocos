#include "MainScene.h"

USING_NS_CC;

MainScene::MainScene()
{
}

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
    for (int i=0; i<3; i++)
    {
	    this->lemmings.push_back(this->addLemming(_middleScreen.x + (60.f * i), _middleScreen.y));
    }

	this->addWindowsEdgesCollider();
}

void MainScene::update(float delta)
{
    Node::update(delta);

    for(const auto &spLemming : this->lemmings)
    {
	    const Vec2 _objPos = spLemming->getPosition();
		const Vec2 _objSize = spLemming->getContentSize();

        // Change direction when hitting a wall 
		if ((_objPos.x + _objSize.x) >= this->visibleSize.width || (_objPos.x + _objSize.x) <= 0) this->lemmingAcceleration *= -1;

        // Change acceleration to null if lemming is in the air (vertical fall)
        //if (_objPos.y > 0) this->lemmingAcceleration *= 0;

		const float _movementDelta = this->lemmingVelocity * delta;
		const float _newObjPosX = (_objPos.x + _movementDelta) * this->lemmingAcceleration;

		spLemming->setPositionX(_newObjPosX);
    }
}

void MainScene::addWindowsEdgesCollider()
{
    const auto body = cocos2d::PhysicsBody::createEdgeBox(visibleSize, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT,1);

    const auto edgeShape = cocos2d::Node::create();
    edgeShape->setPhysicsBody(body);
    edgeShape->setPosition(visibleSize.width / 2, visibleSize.height / 1.7f);
    this->addChild(edgeShape);
}

cocos2d::Sprite* MainScene::addLemming(float positionX, float positionY)
{
    const auto _sp = Sprite::create("HelloWorld.png");
    if (_sp == nullptr) throw ERROR_BAD_PATHNAME;

    _sp->setScale(0.5f);
    _sp->setPosition(positionX, positionY);
    this->addChild(_sp);

    const auto _lemmingPhysicBody = cocos2d::PhysicsBody::createBox(
        cocos2d::Size(_sp->getContentSize()),
        cocos2d::PhysicsMaterial(0.1f,1.0f,0.0f)
    );
    _lemmingPhysicBody->setDynamic(true);
    _lemmingPhysicBody->setGravityEnable(true);
	_sp->addComponent(_lemmingPhysicBody);

    return _sp;
}
