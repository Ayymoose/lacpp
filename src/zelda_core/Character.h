#pragma once

#include "core/Vector.h"
#include "core/Direction.h"

namespace zelda::core
{
class Character
{
public:
    virtual ~Character() = default;

    Character() = default;

protected:
    engine::Vector<float> position() const
    {
        return m_position;
    }

    engine::Direction direction() const
    {
        return m_direction;
    }

    float health() const
    {
        return m_health;
    }

    float m_health{0};

    engine::Vector<float> m_position;

    engine::Direction m_direction{engine::Direction::NONE};
};

} // namespace zelda::core