#pragma once

#include "core/Sprite.h"
#include "core/Vector.h"

// A Renderable is an object that will be rendered on the screen
// A Sprite is provided to use for the derived

namespace zelda::engine
{

class Renderable
{
public:
    virtual ~Renderable() = default;

    virtual void render() = 0;

    Renderable(const char* name, const Sprite& texture, int depth)
        : m_sprite(std::make_unique<Sprite>(texture))
        , m_width(0)
        , m_height(0)
        , m_srcRect({0, 0, 0, 0})
        , m_dstRect({0, 0, 0, 0})
        , m_name(name)
        , m_depth(depth)
    {
        assert(depth > 0);
    }

    Renderable() = delete;

    int depth() const
    {
        assert(m_depth > 0);
        return m_depth;
    }

    std::string name() const
    {
        assert(!m_name.empty());
        return m_name;
    }

protected:
    // Default texture to render
    std::unique_ptr<Sprite> m_sprite;

    // Dimensions
    int m_width;
    int m_height;

    // For sprite
    Rect<int> m_srcRect;
    Rect<float> m_dstRect;

    // Debug name
    std::string m_name;

    // Z-ordering
    int m_depth;
};

} // namespace zelda