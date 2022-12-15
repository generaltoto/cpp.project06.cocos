#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	MainScene* _sceneWithPhysics = MainScene::create();
	_sceneWithPhysics->initWithPhysics();
	_sceneWithPhysics->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
	return _sceneWithPhysics;
}

bool MainScene::init()
{
	if (!Scene::initWithPhysics()) return false;

	m_visibleSize = designResolutionSize;
	m_visibleOrigin = { 0, 0 };

	cocos2d::EventListenerPhysicsContact* _contactListener = EventListenerPhysicsContact::create();

	_contactListener->onContactPostSolve = CC_CALLBACK_1(MainScene::onContactPostSolve, this);
	_contactListener->onContactPreSolve = CC_CALLBACK_1(MainScene::onContactPreSolve, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_contactListener, this);

	scheduleUpdate();

	return true;
}

void MainScene::onEnter()
{
	cocos2d::Scene::onEnter();

	const Vec2 _middleScreen = { m_visibleSize.width / 2, m_visibleSize.height / 2 };
	for (int i = 0; i < 3; i++) addLemming(_middleScreen.x + (300.f * i), _middleScreen.y);
	addWindowsEdgesCollider();
}

void MainScene::update(float delta)
{
	Node::update(delta);

	for (const auto& lem : this->m_lemmings)
	{
		lem->checkIfFalling();
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
	if (_shapeA->getCollisionBitmask() == lemming_collision_mask_id && _shapeB->getCollisionBitmask() == window_collision_mask_id
		|| _shapeA->getCollisionBitmask() == window_collision_mask_id && _shapeB->getCollisionBitmask() == lemming_collision_mask_id
		)
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
	cocos2d::PhysicsBody* _body = cocos2d::PhysicsBody::createEdgeBox(
		{ m_visibleSize.width, m_visibleSize.height + 2 },
		cocos2d::PhysicsMaterial(cocos2d::PHYSICSBODY_MATERIAL_DEFAULT),
		1
	);
	_body->setCategoryBitmask(window_collision_mask_id);
	_body->setCollisionBitmask(lemming_collision_mask_id);
	_body->setContactTestBitmask(test_collision_mask_id);
	_body->setName(window_collision_name_template);

	cocos2d::Node* _edgeShape = cocos2d::Node::create();
	_edgeShape->setPhysicsBody(_body);
	_edgeShape->setPosition(
		m_visibleOrigin.x + m_visibleSize.width / 2,
		m_visibleOrigin.y + m_visibleSize.height / 2
	);
	addChild(_edgeShape);
}

void MainScene::addLemming(float positionX, float positionY)
{
	Lemming* _l = Lemming::create("HelloWorld.png", { positionX, positionY });
	addChild(_l);
	m_lemmings.push_back(_l);
	m_indexedLemmings.insert(std::make_pair(_l->getName(), _l));
}

void MainScene::lemmingContactWithWindowBordersCallback(Lemming* lemming)
{
	PhysicsBody* _body = lemming->getPhysicsBody();
	Vec2 _curVelocity = _body->getVelocity();

	if (isFloatNull(_curVelocity.x) && isFloatNull(_curVelocity.y) && lemming->m_currentState == WALKING)
	{
		lemming->m_currentAcceleration *= -1;
		_body->setVelocity({ _curVelocity.x * lemming->m_currentAcceleration, _curVelocity.y });
	}
	if (isFloatNull(_curVelocity.y) && lemming->m_currentState == FALLING)
	{
		_body->setVelocity({ lemming->m_lemmingVelocity,0 });
		lemming->m_currentState = WALKING;
	}
}

Lemming* MainScene::getLemmingWithName(const std::string& name) const
{
	const auto it = m_indexedLemmings.find(name);
	if (it == m_indexedLemmings.end()) return nullptr;
	return it->second;
}
