#include "HelloWorldScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if ( !Scene::init() ) return false;

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    m_pMap = new TileMap("../Resources/map/Test.tmx");

    addChild(m_pMap->getMap());
    return true;
}

void MainScene::onEnter()
{
    Scene::onEnter();

    cocos2d::Sprite* mySprite = cocos2d::Sprite::create("../Resources/map/netherPortal.png");
    mySprite->setPosition(m_pMap->getSpawnPoint());
    addChild(mySprite);
    /*_defaultCamera->initOrthographic(200, 200, 1, 2000);
    _defaultCamera->setPosition(0, 0);*/
}
