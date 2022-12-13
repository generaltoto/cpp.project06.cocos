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

	const auto _contactListener = cocos2d::EventListenerPhysicsContact::create();
	_contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContact, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_contactListener, this);

	this->scheduleUpdate();

	return true;
}

void MainScene::onEnter()
{
	cocos2d::Layer::onEnter();

	const Vec2 _middleScreen = { visibleSize.width / 2, visibleSize.height / 2 };
	for (int i = 0; i < 3; i++) this->addLemming(_middleScreen.x + (300.f * i), _middleScreen.y);
	this->addWindowsEdgesCollider();
}

void MainScene::update(float delta)
{
	Node::update(delta);

	for (const auto& lem : this->lemmings)
	{
		lem->updateVelocity(delta, this->visibleSize, this->visibleOrigin, 0.f);
	}
}

void MainScene::addWindowsEdgesCollider()
{
	const auto _body = cocos2d::PhysicsBody::createEdgeBox({ visibleSize.width, visibleSize.height + 2 }, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, 1);
	_body->setCategoryBitmask(window_collision_mask_id);
	_body->setCollisionBitmask(lemming_collision_mask_id);

	const auto _edgeShape = cocos2d::Node::create();
	_edgeShape->setPhysicsBody(_body);
	_edgeShape->setPosition(
		this->visibleOrigin.x + this->visibleSize.width / 2,
		this->visibleOrigin.y + this->visibleSize.height / 2
	);
	this->addChild(_edgeShape);
}

void MainScene::addLemming(float positionX, float positionY)
{
	const auto _l = Lemming::create("HelloWorld.png", { positionX, positionY });
	this->addChild(_l->sprite);
	this->lemmings.push_back(_l);
}

bool MainScene::onContact(const cocos2d::PhysicsContact& contact)
{
	const cocos2d::PhysicsBody* a = contact.getShapeA()->getBody();
	const cocos2d::PhysicsBody* b = contact.getShapeB()->getBody();

	// Checking if the Lemming collided with a window border
	if (
		(a->getCollisionBitmask() == lemming_collision_mask_id && b->getCollisionBitmask() == window_collision_mask_id) ||
		(a->getCollisionBitmask() == window_collision_mask_id && b->getCollisionBitmask() == lemming_collision_mask_id)
		)
	{
		CCLOG("Collision has occured !!!");
	}
	return true;
}
