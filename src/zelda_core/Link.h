#pragma once

#include "core/Renderable.h"
#include "core/Controllable.h"
#include "core/Updateable.h"
#include "zelda_gui/Worldmap.h"
#include "zelda_core/Character.h"

namespace zelda::core
{

class Link :
    public Character,
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

private:
    float m_maxHealth;
};

} // namespace zelda::core