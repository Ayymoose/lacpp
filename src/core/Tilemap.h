#pragma once

#include <vector>
#include <memory>

#include "core/Sprite.h"
#include "core/Renderer.h"

namespace zelda::engine
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

    Tilemap() = default;

    Tilemap(const Sprite& tilemap, const std::vector<TileIndexArray>& mapEntries, const TilemapConfig& config);

    void tile(const Renderer& renderer, const Sprite& tilemapSprite, size_t mapIndex) const;
    size_t size() const;

private:
    std::unique_ptr<Sprite> m_sprite;
    TilemapConfig m_config{};
    std::vector<TileIndexArray> m_mapEntries;
};


} // namespace zelda::engine
