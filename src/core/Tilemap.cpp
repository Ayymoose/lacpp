#include "core/Tilemap.h"
#include "core/SDL_RenderTarget.h"

namespace zelda::engine
{

Tilemap::Tilemap(const Sprite& tilemap, const std::vector<TileIndexArray>& mapEntries, const TilemapConfig& config)
    : m_sprite(std::make_unique<Sprite>(tilemap))
    , m_config(config)
    , m_mapEntries(mapEntries)
{
    assert(m_sprite->data());
}

void Tilemap::tile(const Renderer& renderer, const Sprite& tilemapSprite, size_t mapIndex) const
{
    assert(static_cast<int>(mapIndex) >= 0 && mapIndex < m_mapEntries.size());
    assert(tilemapSprite.data());

    assert(m_config.tilesDown != 0);
    assert(m_config.tilesAcross != 0);
    assert(m_config.tileHeight != 0);
    assert(m_config.tileWidth != 0);

    const auto& mapEntry = m_mapEntries[mapIndex];
    RenderTarget target(renderer.getRenderer(), tilemapSprite.data());

    // Start painting the canvas with tiles
    for (size_t tileY = 0; tileY < m_config.tilesDown; ++tileY)
    {
        for (size_t tileX = 0; tileX < m_config.tilesAcross; ++tileX)
        {
            // The tile will be the ID in the image
            const auto tileID = mapEntry[tileY][tileX];

            // Calculate where to grab the tile from in the image
            const auto srcTileX = m_config.tileWidth * (tileID % m_config.tilesAcross);
            const auto srcTileY = m_config.tileHeight * (tileID / m_config.tilesAcross);

            // Paste tile from tilemap
            m_sprite->draw(Rect{srcTileX, srcTileY, m_config.tileWidth, m_config.tileHeight},
                           Rect{tileX * m_config.tileWidth,
                                tileY * m_config.tileHeight,
                                m_config.tileWidth,
                                m_config.tileHeight});
        }
    }
}

size_t Tilemap::size() const
{
    return m_mapEntries.size();
}


} // namespace zelda::engine