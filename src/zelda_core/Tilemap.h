#pragma once

#include <vector>
#include <memory>

#include "core/Sprite.h"
#include "core/Renderer.h"

namespace zelda::core
{

class Tilemap
{
public:
    using TileIndexArray = std::vector<std::vector<int>>;

    struct TilemapConfig
    {
        size_t tileWidth;
        size_t tileHeight;
        size_t tilesAcross;
        size_t tilesDown;
    };

    Tilemap();
    Tilemap(const engine::Sprite &tilemap, const std::vector<TileIndexArray> &mapEntries, const TilemapConfig &config);

    void tile(const engine::Renderer &renderer, const engine::Sprite &tilemapSprite, const size_t mapIndex) const;
    size_t size() const;

private:
    std::unique_ptr<engine::Sprite> m_sprite;
    size_t m_tileWidth;
    size_t m_tileHeight;
    size_t m_tilesAcross;
    size_t m_tilesDown;
    std::vector<TileIndexArray> m_mapEntries;
};


} // namespace zelda::core
