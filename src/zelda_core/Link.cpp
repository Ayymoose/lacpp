#include "Link.h"
#include "core/ResourceManager.h"
#include "core/Controller.h"
#include "core/Renderer.h"
#include "core/Camera.h"
#include "zelda_core/Depth.h"

namespace zelda::core
{

Link::Link()
    : Renderable("Link", *engine::ResourceManager::instance()[engine::SpriteResource::LINK],
                 std::to_underlying(core::ZOrdering::PLAYER))
    , Controllable(m_name)
    , m_maxHealth(3)
{
    m_width = 16;
    m_height = 16;

    m_position.x = 72;
    m_position.y = 32;

    engine::Renderer::instance().addRenderable(this);
}

void Link::update()
{
}

void Link::render()
{
    // The render loop calls render() every frame
    // But there are special cases of animation

    // Get clock, if elapsed, increase frame counter
    // Source rect to pull from sprite sheet

    auto cameraPosition = engine::Camera<float>::instance().toCoordinates(m_position);

    // Where to draw on screen
    m_dstRect = {
                 cameraPosition.x,
                 cameraPosition.y,
                 static_cast<float>(m_width),
                 static_cast<float>(m_height)};

    m_sprite->draw(m_srcRect, m_dstRect);
}


void Link::control()
{}

void Link::setHealth(float health)
{
    m_health = health;
}

void Link::setMaxHealth(float maxHealth)
{
    m_maxHealth = maxHealth;
}

float Link::maxHealth() const
{
    return m_maxHealth;
}

void Link::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

} // namespace zelda::core