#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	const auto _sceneWithPhysics = MainScene::create();
	_sceneWithPhysics->initWithPhysics();
	_sceneWithPhysics->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
	return _sceneWithPhysics;
}

bool MainScene::init()
{
	if (!Scene::initWithPhysics()) return false;

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
	cocos2d::Scene::onEnter();

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

bool MainScene::onContactBegin(const cocos2d::PhysicsContact& contact) const
{
	const cocos2d::PhysicsBody* shapeA = contact.getShapeA()->getBody();
	const cocos2d::PhysicsBody* shapeB = contact.getShapeB()->getBody();


	// Checking if a Lemming collided with a window border
	if (shapeA->getCollisionBitmask() == lemming_collision_mask_id && shapeB->getCollisionBitmask() == window_collision_mask_id)
	{
		const Lemming* _l = getLemmingWithName(shapeB->getName());
		if (_l == nullptr) return false;
		MainScene::lemmingContactWithWindowBordersCallback(_l);
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
	_body->setContactTestBitmask(test_collision_mask_id);
	_body->setName(window_collision_name_template);

	const auto _edgeShape = cocos2d::Node::create();
	_edgeShape->setPhysicsBody(_body);
	_edgeShape->setPosition(
		this->visibleOrigin.x + this->visibleSize.width / 2,
		this->visibleOrigin.y + this->visibleSize.height / 2
	);
	this->addChild(_edgeShape);
}

void MainScene::addLemming(int index, float positionX, float positionY)
{
	Lemming* _l = Lemming::create("HelloWorld.png", { positionX, positionY });
	addChild(_l);
	lemmings.push_back(_l);
	indexedLemmings.insert(std::make_pair(_l->getName(), _l));
}

void MainScene::lemmingContactWithWindowBordersCallback(const Lemming* lemming)
{
	PhysicsBody* _body = lemming->getPhysicsBody();
	Vec2 _curVelocity = _body->getVelocity();
	if(isFloatNull(_curVelocity.x) && isFloatNull(_curVelocity.y) && lemming->currentState != SPAWNING)
	{
		_body->setVelocity({ _curVelocity.x * -1, _curVelocity.y });
	}
}

Lemming* MainScene::getLemmingWithName(const std::string &name) const
{
	const auto it = indexedLemmings.find(name);
	if ( it==indexedLemmings.end()) return nullptr;
	return it->second;
 }
