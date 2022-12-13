#include "MainScene.h"

USING_NS_CC;

MainScene::MainScene()
{
    this->spLemming = nullptr;
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

    return true;
}

void MainScene::onEnter()
{
    cocos2d::Layer::onEnter();
	this->addLemming(visibleSize.width / 2, visibleSize.height / 2);
	this->addWindowsEdgesCollider();
}

void MainScene::update(float delta)
{
    Node::update(delta);

    const float _curPosX = this->spLemming->getPositionX();
    this->spLemming->setPositionX(_curPosX + 10 * delta);
}

void MainScene::addWindowsEdgesCollider()
{
    const auto body = cocos2d::PhysicsBody::createEdgeBox(visibleSize, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT,1);

    const auto edgeShape = cocos2d::Node::create();
    edgeShape->setPhysicsBody(body);
    edgeShape->setPosition(visibleSize.width / 2, visibleSize.height / 1.7f);
    this->addChild(edgeShape);
}

void MainScene::addLemming(float positionX, float positionY)
{
    this->spLemming = Sprite::create("HelloWorld.png");
    if (this->spLemming == nullptr) throw ERROR_BAD_PATHNAME;

    this->spLemming->setPosition(positionX, positionY);
    this->addChild(this->spLemming);

    const auto _lemmingPhysicBody = cocos2d::PhysicsBody::createBox(
        cocos2d::Size(this->spLemming->getContentSize()),
        cocos2d::PhysicsMaterial(0.1f,1.0f,0.0f)
    );
    _lemmingPhysicBody->setDynamic(true);
    _lemmingPhysicBody->setGravityEnable(true);
	this->spLemming->addComponent(_lemmingPhysicBody);
}
