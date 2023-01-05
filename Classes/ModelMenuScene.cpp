#include "ModelMenuScene.h"

bool ModelMenuScene::init()
{
	if (!Scene::init()) return false;

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_visibleOrigin = Director::getInstance()->getVisibleOrigin();

	return true;
}

MenuItemImage* ModelMenuScene::CreateCloseItem()
{
	MenuItemImage* _closeItem = MenuItemImage::create(
		menu_closeButton_path,
		menu_closeButton_selected_path,
		CC_CALLBACK_1(ModelMenuScene::MenuCloseCallback, this)
	);
	assert(_closeItem);
	_closeItem->setPosition(Vec2(
		m_visibleOrigin.x + m_visibleSize.width - _closeItem->getContentSize().width / 2, 
		m_visibleOrigin.y + _closeItem->getContentSize().height / 2)
	);
	return _closeItem;
}

MenuItemFont* ModelMenuScene::CreateReturnButton(Vec2 position)
{
	MenuItemFont* _menuQuit = MenuItemFont::create("Quit",CC_CALLBACK_1(ModelMenuScene::ReturnToScene, this));
	_menuQuit->setPosition(position);
	_menuQuit->setFontSizeObj(40);
	return _menuQuit;
}

void ModelMenuScene::CreateTitle()
{
	Label* _label = Label::createWithTTF("Save the Steves", font_path, 80);
	assert(_label);
	_label->setPosition(Vec2(m_visibleOrigin.x + m_visibleSize.width / 2,
		m_visibleOrigin.y + m_visibleSize.height - _label->getContentSize().height)
	);
	_label->setTextColor(Color4B(0, 0, 0, 255));
	_label->enableOutline(Color4B(245, 245, 245, 255), 4);
	addChild(_label, 1);
}

void ModelMenuScene::CreateBackground(const char* path, float scale)
{
	Sprite* _bg = Sprite::create(path);
	assert(_bg);
	_bg->setPosition(Vec2(m_visibleSize.width / 2 + m_visibleOrigin.x,m_visibleSize.height / 2 + m_visibleOrigin.y));
	_bg->setScale(scale);
	addChild(_bg, 0);
}

void ModelMenuScene::CreateDynamicMenu()
{
	Menu* _menu = Menu::create(CreateCloseItem(), NULL);
	_menu->setPosition(Vec2::ZERO);
	addChild(_menu, 1);
}

void ModelMenuScene::PlayMenuSoundEffect()
{
	//AudioEngine::play2d(audio_menu_path, false, 1.0f);
}

void ModelMenuScene::ReturnToScene(Ref* pSender) 
{ 
	//PlayMenuSoundEffect();
	Director::getInstance()->popScene(); 
}

void ModelMenuScene::update(float delta) { Scene::update(delta); }

void ModelMenuScene::MenuCloseCallback(Ref* pSender) 
{ 
	//PlayMenuSoundEffect();
	Director::getInstance()->end(); 
}