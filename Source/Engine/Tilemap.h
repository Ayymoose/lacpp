#pragma once

#include <vector>
#include <memory>

#include "Sprite.h"
#include "Renderer.h"

namespace Zelda
{

    class Tilemap
    {
    public:

        using TileIndexArray = std::vector<std::vector<int>>;

        struct TilemapConfig
        {
            size_t tilemapWidth;
            size_t tileWidth;
            size_t tileHeight;
            size_t tilesAcross;
            size_t tilesDown;
        };

        Tilemap();
        Tilemap(const Sprite& tilemap, const std::vector<TileIndexArray>& mapEntries, const TilemapConfig& config);
    
        void tile(const Renderer& renderer, const Sprite& tilemapSprite, size_t mapIndex) const;
        size_t size() const;

    private:
        std::unique_ptr<Sprite> m_sprite;
        size_t m_tilemapWidth;
        size_t m_tileWidth;
        size_t m_tileHeight;
        size_t m_tilesAcross;
        size_t m_tilesDown;
        std::vector<TileIndexArray> m_mapEntries;
    };


}
