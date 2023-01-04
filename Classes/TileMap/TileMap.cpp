#include "TileMap.h"

// #### Private functions #### //
void TileMap::initVariables()
{
    m_pMap = nullptr;
    m_pBackground = nullptr;
}

void TileMap::initMap(std::string tileMapPath)
{
    m_pMap = TMXTiledMap::create(tileMapPath);
    m_pBackground = m_pMap->getLayer("Background");
    m_pCollision = m_pMap->getLayer("Collision");
    

    for (int i = 0; i < m_pCollision->getLayerSize().width; i++)
    {
        for (int j = 0; j < m_pCollision->getLayerSize().height; j++)
        {
            if (m_pCollision->getTileAt(Vec2(i,j)) == nullptr) continue;
            PhysicsBody* pB = PhysicsBody::createBox(
                Size(m_pCollision->getTileSet()->_tileSize) - Size(7, 7),
                PhysicsMaterial(PHYSICSBODY_MATERIAL_DEFAULT));

            pB->setCategoryBitmask(window_collision_mask_id);
            pB->setDynamic(false);
            m_pCollision->getTileAt(Vec2(i,j))->setPhysicsBody(pB);
        }
    }
    m_pEntities = m_pMap->getObjectGroup("Entities");
    
    m_spawnPoint = { m_pEntities->getObject("Player")["x"].asFloat(), m_pEntities->getObject("Player")["y"].asFloat() };

    m_pCollision->setTileGID(0, Vec2(12, 11));
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

TMXTiledMap* TileMap::getMap()
{
    return m_pMap;
}

Vec2 TileMap::getSpawnPoint()
{
    return m_spawnPoint;
}

bool TileMap::removeTileUnder(Vec2 lemmingPosition)
{
    Vec2 tileSize = m_pMap->getTileSize();
    auto collideLayerSize = m_pCollision->getLayerSize();

    auto tilePos = Vec2(floor(lemmingPosition.x / tileSize.x), round(lemmingPosition.y / tileSize.y));
    tilePos.x += 1;
    tilePos.y = collideLayerSize.height - tilePos.y;

    if (tilePos.x >= collideLayerSize.width || tilePos.y >= collideLayerSize.height
        || tilePos.x < 0 || tilePos.y < 0) return false;

    if (!m_pCollision->getTileAt(tilePos)) return false;

    m_pCollision->setTileGID(0, tilePos);
    return true;
}
