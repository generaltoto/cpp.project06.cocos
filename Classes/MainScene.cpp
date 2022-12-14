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

	_contactListener->onContactPostSolve = CC_CALLBACK_1(MainScene::onContactPostSolve, this);
	_contactListener->onContactPreSolve = CC_CALLBACK_1(MainScene::onContactPreSolve, this);

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

bool MainScene::onContactPreSolve(cocos2d::PhysicsContact& contact) const
{
	cocos2d::PhysicsBody* _shapeA = contact.getShapeA()->getBody();
	cocos2d::PhysicsBody* _shapeB = contact.getShapeB()->getBody();

	// Saving velocity to restore it at the end of collide (prevent from friction slow down)
	const auto _velocityData = new float[2];
	_velocityData[0] = _shapeA->getVelocity().length();
	_velocityData[1] = _shapeB->getVelocity().length();
	contact.setData(_velocityData);
	// See MainScene::onContactPostSolve for use of saved data

	// Checking if a Lemming collided with a window border
	if (_shapeA->getCollisionBitmask() == lemming_collision_mask_id && _shapeB->getCollisionBitmask() == window_collision_mask_id)
	{
		Lemming* _l = getLemmingWithName(_shapeB->getName());
		if (_l == nullptr) return false;
		MainScene::lemmingContactWithWindowBordersCallback(_l);
		return true;
	}
	return false;
}

bool MainScene::onContactPostSolve(const cocos2d::PhysicsContact& contact) const
{
	PhysicsBody* _shapeA = contact.getShapeA()->getBody();
	PhysicsBody* _shapeB = contact.getShapeB()->getBody();

	/*
	 * Restoring the velocity, keeping the direction of the velocity.
	 * Does not restore the y velocity. You you want to, replace '{ va.x * v[0], 0 }' by 'va.x * v[0]'.
	 */
	Vec2 _va = _shapeA->getVelocity();
	Vec2 _vb = _shapeB->getVelocity();
	_va.normalize();
	_vb.normalize();

	const auto _v = static_cast<float*>(contact.getData());
	_shapeA->setVelocity({ _va.x * _v[0], 0 });
	_shapeB->setVelocity({ _vb.x * _v[1], 0 });
	delete _v;

	return true;
}

void MainScene::addWindowsEdgesCollider()
{
	const auto _body = cocos2d::PhysicsBody::createEdgeBox(
		{ visibleSize.width, visibleSize.height + 2 },
		cocos2d::PhysicsMaterial(cocos2d::PHYSICSBODY_MATERIAL_DEFAULT),
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

void MainScene::lemmingContactWithWindowBordersCallback(Lemming* lemming)
{
	PhysicsBody* _body = lemming->getPhysicsBody();
	Vec2 _curVelocity = _body->getVelocity();

	const bool a = isFloatNull(_curVelocity.x);
	const bool b = isFloatNull(_curVelocity.y);

	if (isFloatNull(_curVelocity.x) && isFloatNull(_curVelocity.y) && lemming->currentState == WALKING)
	{
		lemming->currentAcceleration *= -1;
		_body->setVelocity({ _curVelocity.x * lemming->currentAcceleration, _curVelocity.y });
	}
	if (isFloatNull(_curVelocity.y) && lemming->currentState == FALLING)
	{
		_body->setVelocity({ lemming->lemmingVelocity,0 });
		lemming->currentState = WALKING;
	}
}

Lemming* MainScene::getLemmingWithName(const std::string& name) const
{
	const auto it = indexedLemmings.find(name);
	if (it == indexedLemmings.end()) return nullptr;
	return it->second;
}
