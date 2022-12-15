#include "TileMap.h"

// #### Private functions #### //
void TileMap::initVariables()
{
    m_pMap = nullptr;
    m_pBackground = nullptr;
}

void TileMap::initMap(std::string tileMapPath)
{
    m_pMap = cocos2d::TMXTiledMap::create(tileMapPath);
    m_pBackground = m_pMap->getLayer("Background");
    m_pCollision = m_pMap->getObjectGroup("Collision");
    m_pEntities = m_pMap->getObjectGroup("Entities");
    
    m_spawnPoint = { m_pEntities->getObject("Player")["x"].asFloat(), m_pEntities->getObject("Player")["y"].asFloat() };
}
// #### Private functions #### //

TileMap::TileMap(std::string tileMapPath)
{
    initVariables();
    initMap(tileMapPath);
}

TileMap::~TileMap()
{
}

cocos2d::TMXTiledMap* TileMap::getMap()
{
    return m_pMap;
}

cocos2d::Vec2 TileMap::getSpawnPoint()
{
    return m_spawnPoint;
}
