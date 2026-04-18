#pragma once

#include "Vector.h"
#include "Depth.h"
#include "Enum.h"

namespace Zelda
{

    class BasicCharacter
    {
    public:
        virtual ~BasicCharacter() = default;
        virtual float health() const = 0;
        virtual Vector<float> position() const = 0;
    protected:
        BasicCharacter() : m_dir(Direction::DIRECTION_NONE), m_health(0), m_speed(0)
        {
        }

        // Character direction
        Direction m_dir;

        // Character health
        float m_health;
        float m_speed;

        // Position vector
        Vector<float> m_position;

        // Direction vector
        Vector<float> m_direction;
    };

}