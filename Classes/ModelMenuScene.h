#pragma once

#include "2d/CCScene.h"
#include "2d/CCMenuItem.h"
#include "../proj.win32/Constants.h"

USING_NS_CC;

class ModelMenuScene : public Scene
{
public:
	Size m_visibleSize;
	Vec2 m_visibleOrigin;

	/**
	 * \brief Inits the different elements of the scene.
	 * \return True if good init or false if bad init.
	 */
	bool init() override;

	/**
	 * \brief Updates the scene with a given time.
	 */
	void update(float) override;

	CREATE_FUNC(ModelMenuScene);

protected:

	MenuItemImage* createCloseItem();

	MenuItemFont* createReturnButton(Vec2);

	void menuCloseCallback(Ref*);

	void returnToScene(Ref*);

	void createTitle();

	void createBackground(const char*, float);

	virtual void CreateDynamicMenu();
};
