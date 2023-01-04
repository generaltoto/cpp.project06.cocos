#pragma once
#include "2d/CCTMXTiledMap.h"
#include "2d/CCTMXLayer.h"
#include "2d/CCSprite.h"
#include "math/Vec2.h"
#include "../proj.win32/Paths.h"
#include "../proj.win32/Bitmasks.h"

USING_NS_CC;

class TileMap
{
public:
    TileMap(std::string tileMapPath);
    ~TileMap();

    TMXTiledMap* getMap();
    Vec2 getSpawnPoint();

    TMXLayer* GetCollisions() const { return m_pCollision; }
    void updateCollisions(TMXLayer* col) { m_pCollision = col; }

    bool removeTileUnder(Vec2 lemmingPosition) const;
    bool removeTileLeft(Vec2 lemmingPosition) const;
    bool removeTileRight(Vec2 lemmingPosition) const;

private:
    TMXTiledMap* m_pMap;
    TMXLayer* m_pBackground;
    TMXLayer* m_pCollision;
    TMXObjectGroup* m_pEntities;

    Vec2 m_spawnPoint;

    void initVariables();
    void initMap(std::string tileMapPath);
};
