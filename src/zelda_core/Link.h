#pragma once

#include "core/Renderable.h"
#include "core/Controllable.h"
#include "core/Updateable.h"
#include "zelda_gui/Worldmap.h"
#include "core/Vector.h"

namespace zelda::core
{

class Link :
    public engine::Renderable,
    public engine::Controllable,
    public engine::Singleton<Link>,
    public engine::Updateable
{
public:
    Link();

    void render() override;

    void update() override;

    void control() override;

    void setPosition(float x, float y);

    void setHealth(float health);

    void setMaxHealth(float maxHealth);

    float maxHealth() const;

    // Overrides
    float health() const;

    engine::Direction direction() const;

    engine::Vector<float> position() const;

private:
    float m_maxHealth;

    //

    float m_health;

    engine::Vector<float> m_position;

    engine::Direction m_direction;
};

} // namespace zelda::core