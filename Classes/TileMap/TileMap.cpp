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
    m_pCollision = m_pMap->getLayer("Collision");
    auto tt = m_pCollision->getTiles()[599];
    

    for (int i = 0; i < m_pCollision->getLayerSize().width; i++)
    {
        for (int j = 0; j < m_pCollision->getLayerSize().height; j++)
        {
            if (m_pCollision->getTileAt(cocos2d::Vec2(i,j)) == nullptr) continue;
            cocos2d::PhysicsBody* pB = cocos2d::PhysicsBody::createBox(
                cocos2d::Size(m_pCollision->getTileSet()->_tileSize) - cocos2d::Size(4, 4),
                cocos2d::PhysicsMaterial(cocos2d::PHYSICSBODY_MATERIAL_DEFAULT));

            pB->setCategoryBitmask(window_collision_mask_id);
            pB->setDynamic(false);
            m_pCollision->getTileAt(cocos2d::Vec2(i,j))->setPhysicsBody(pB);
        }
    }
    m_pEntities = m_pMap->getObjectGroup("Entities");
    
    m_spawnPoint = { m_pEntities->getObject("Player")["x"].asFloat(), m_pEntities->getObject("Player")["y"].asFloat() };

    m_pCollision->setTileGID(0, cocos2d::Vec2(20, 18));
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

cocos2d::Sprite* TileMap::getTileUnder(cocos2d::Vec2 lemmingPosition)
{
    cocos2d::Vec2 tileSize = m_pMap->getTileSize();
    auto collideLayerSize = m_pCollision->getLayerSize();

    auto tilePos = cocos2d::Vec2(floor(lemmingPosition.x / tileSize.x), floor(lemmingPosition.y / tileSize.y));
    tilePos.y = collideLayerSize.height - tilePos.y;

    if (tilePos.x >= collideLayerSize.width || tilePos.y >= collideLayerSize.height
        || tilePos.x < 0 || tilePos.y < 0) return nullptr;

    return m_pCollision->getTileAt(tilePos);
}

bool TileMap::removeTileUnder(cocos2d::Vec2 lemmingPosition)
{
    cocos2d::Vec2 tileSize = m_pMap->getTileSize();
    auto collideLayerSize = m_pCollision->getLayerSize();

    auto tilePos = cocos2d::Vec2(floor(lemmingPosition.x / tileSize.x), floor(lemmingPosition.y / tileSize.y));
    tilePos.y = collideLayerSize.height - tilePos.y;

    if (tilePos.x >= collideLayerSize.width || tilePos.y >= collideLayerSize.height
        || tilePos.x < 0 || tilePos.y < 0) return false;

    if (!m_pCollision->getTileAt(tilePos)) return false;

    m_pCollision->setTileGID(0, tilePos);
    return true;
}
