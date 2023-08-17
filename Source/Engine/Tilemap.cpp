#include "Tilemap.h"

namespace Zelda
{

    Tilemap::Tilemap() : m_tilemapWidth(0), m_tileWidth(0), m_tileHeight(0), m_tilesAcross(0), m_tilesDown(0)
    {
    }

    Tilemap::Tilemap(const Sprite& tilemap, const std::vector<TileIndexArray>& mapEntries, const TilemapConfig& config) 
        : m_sprite(std::make_unique<Sprite>(tilemap)),
        m_mapEntries(mapEntries), 
        m_tilemapWidth(config.tilemapWidth),
        m_tileWidth(config.tileWidth),
        m_tileHeight(config.tileHeight),
        m_tilesAcross(config.tilesAcross),
        m_tilesDown(config.tilesDown)
    {
        assert(m_sprite->data());
    }

    void Tilemap::tile(const Renderer& renderer, const Sprite& tilemapSprite, size_t mapIndex) const
    {
        assert(mapIndex >= 0 && mapIndex < m_mapEntries.size());
        assert(tilemapSprite.data());

        assert(m_tilemapWidth != 0);
        assert(m_tileWidth != 0);

        auto const tileMapTilesAcross = (m_tilemapWidth / m_tileWidth);

        auto const target = renderer.pushRenderingTarget(tilemapSprite);
        auto const mapEntry = m_mapEntries[mapIndex];

        assert(m_tilesDown != 0);
        assert(m_tilesAcross != 0);
        assert(m_tileHeight != 0);

        // Start painting the canvas with tiles
        for (size_t tileY = 0; tileY < m_tilesDown; tileY++)
        {
            for (size_t tileX = 0; tileX < m_tilesAcross; tileX++)
            {
                // The tile will be the ID in the image
                auto const tileID = mapEntry[tileY][tileX];

                // Calculate where to grab the tile from in the image
                auto const srcTileX = m_tileWidth * (tileID % tileMapTilesAcross);
                auto const srcTileY = m_tileHeight * (tileID / tileMapTilesAcross);

                // Paste tile from tilemap
                m_sprite->drawSprite(
                    Rect<size_t>
                    {
                        srcTileX,
                        srcTileY,
                        m_tileWidth,
                        m_tileHeight
                    },
                    Rect<size_t>
                    {
                        tileX * m_tileWidth,
                        tileY * m_tileHeight,
                        m_tileWidth,
                        m_tileHeight
                    }
                );
            }
        }
        renderer.popRenderingTarget(target);
    }

    size_t Tilemap::size() const
    {
        return m_mapEntries.size();
    }


}