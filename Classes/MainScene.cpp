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
	if (!Layer::init()) return false;

	this->visibleSize = designResolutionSize;
	this->visibleOrigin = { 0, 0 };

	const auto _contactListener = EventListenerPhysicsContact::create();
	_contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_contactListener, this);

	this->scheduleUpdate();

	return true;
}

void MainScene::onEnter()
{
	cocos2d::Layer::onEnter();

	const Vec2 _middleScreen = { visibleSize.width / 2, visibleSize.height / 2 };
	for (int i = 0; i < 3; i++) this->addLemming(i, _middleScreen.x + (300.f * i), _middleScreen.y);
	this->addWindowsEdgesCollider();
}

void MainScene::update(float delta)
{
	Node::update(delta);

	for (const auto& lem : this->lemmings)
	{
		lem->updateForces(delta, 0.f);
	}
}

bool MainScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	cocos2d::PhysicsBody* a = contact.getShapeA()->getBody();
	cocos2d::PhysicsBody* b = contact.getShapeB()->getBody();

	// Checking if a Lemming collided with a window border
	if (a->getCollisionBitmask() == lemming_collision_mask_id && b->getCollisionBitmask() == window_collision_mask_id)
	{
		MainScene::lemmingContactWithWindowBordersCallback(a);
		return true;
	}
	if (a->getCollisionBitmask() == window_collision_mask_id && b->getCollisionBitmask() == lemming_collision_mask_id)
	{
		MainScene::lemmingContactWithWindowBordersCallback(b);
		return true;
	}
	return false;
}

void MainScene::addWindowsEdgesCollider()
{
	const auto _body = cocos2d::PhysicsBody::createEdgeBox(
		{ visibleSize.width, visibleSize.height + 2 }, 
		cocos2d::PhysicsMaterial(100.f, 0.f, 1.f),
		1
	);
	_body->setCategoryBitmask(window_collision_mask_id);
	_body->setCollisionBitmask(lemming_collision_mask_id);

	const auto _edgeShape = cocos2d::Node::create();
	_edgeShape->setPhysicsBody(_body);
	_edgeShape->setPosition(
		this->visibleOrigin.x + this->visibleSize.width / 2,
		this->visibleOrigin.y + this->visibleSize.height / 2
	);
	_edgeShape->setName(window_collision_name_template);
	this->addChild(_edgeShape);
}

void MainScene::addLemming(int index, float positionX, float positionY)
{
	const auto _l = Lemming::create("HelloWorld.png", { positionX, positionY }, index);
	this->addChild(_l);
	this->lemmings.push_back(_l);
}

void MainScene::lemmingContactWithWindowBordersCallback(PhysicsBody* target)
{
	CCLOG("Collision has occured !!!");

	const auto _curVelocity = target->getVelocity();

	target->setVelocity({ _curVelocity.x * -1, _curVelocity.y });
}
