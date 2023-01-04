#pragma once

#include "2d/CCScene.h"
#include "2d/CCMenuItem.h"
#include "2d/CCSprite.h"
#include "2d/CCLabel.h"
#include "2d/CCMenu.h"
#include "CCDirector.h"
#include "../proj.win32/Paths.h"
#include "../proj.win32/ScreenSizes.h"

USING_NS_CC;

class ModelMenuScene : public Scene
{
public:
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

	Size m_visibleSize;
	Vec2 m_visibleOrigin;

	MenuItemImage* CreateCloseItem();

	MenuItemFont* CreateReturnButton(Vec2);

	void MenuCloseCallback(Ref*);

	void ReturnToScene(Ref*);

	void CreateTitle();

	void CreateBackground(const char*, float);

	virtual void CreateDynamicMenu();
};
