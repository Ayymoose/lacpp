#pragma once

#include "core/Vector.h"
#include "Depth.h"
#include "Enum.h"

namespace zelda
{

class BasicCharacter
{
public:
    virtual ~BasicCharacter() = default;
    virtual float health() const = 0;
    virtual engine::Vector<float> position() const = 0;

protected:
    BasicCharacter()
        : m_dir(core::Direction::NONE)
        , m_health(0)
        , m_speed(0)
    {}

    // Character direction
    core::Direction m_dir;

    // Character health
    float m_health;
    float m_speed;

    // Position vector
    engine::Vector<float> m_position;

    // Direction vector
    engine::Vector<float> m_direction;
};

} // namespace zelda