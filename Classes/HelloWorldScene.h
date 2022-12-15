#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "TileMap/TileMap.h"

class MainScene : public cocos2d::Scene
{
private:
    TileMap* m_pMap;
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    void onEnter() override;

    CREATE_FUNC(MainScene);
};

#endif // __HELLOWORLD_SCENE_H__
