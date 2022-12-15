#pragma once
#include "cocos2d.h"

class TileMap
{
private:
    cocos2d::TMXTiledMap* m_pMap;
    cocos2d::TMXLayer* m_pBackground;
    cocos2d::TMXObjectGroup* m_pCollision;
    cocos2d::TMXObjectGroup* m_pEntities;

    cocos2d::Vec2 m_spawnPoint;

    void initVariables();
    void initMap(std::string tileMapPath);
public:
    TileMap(std::string tileMapPath);
    ~TileMap();

    cocos2d::TMXTiledMap* getMap();
    cocos2d::Vec2 getSpawnPoint();
};
