#include "BladeTrap.h"
#include "Link.h"

BladeTrap::BladeTrap(int x, int y) : Enemy(x, y)
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_ENEMY];
    m_direction = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;

    m_range = m_width * 3;

    m_speed = 1.5f;
    m_retreatSpeed = m_speed / 2;

    m_attack = false;
    m_retreat = false;
    m_moved = 0;

    m_name = "Blade Trap";
    m_depth = ZD_DEPTH_ENEMY;
    Renderer::getInstance().addRenderable(this);
}

void BladeTrap::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[static_cast<size_t>(EnemySprite::ENEMY_BLADETRAP)];

    m_animateXPos = animation.x;
    m_animateYPos = animation.y;
    m_endFrame = animation.endFrame;
    m_animationFPS = animation.animationFPS;

    m_srcRect =
    {
        m_animateXPos + (m_currentFrame * m_width),
        m_animateYPos,
        m_width,
        m_height
    };

    // Where to draw on screen
    m_dstRect =
    {
        m_positionVector.x - static_cast<float>(Camera::getInstance().getX()),
        m_positionVector.y - static_cast<float>(Camera::getInstance().getY()),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    ZD_ASSERT(SDL_RenderCopyF(renderer, m_texture, &m_srcRect, &m_dstRect) == 0, "SDL Error: " << SDL_GetError());

    if (m_animationTimer.elapsed(m_animationFPS) && !Engine::getInstance().paused())
    {
        if (m_currentFrame < m_endFrame)
        {
            m_currentFrame++;
        }
        else
        {
            m_currentFrame = animation.startFrame;
        }
        m_animationTimer.reset();
    }

    /*ZD_ASSERT(SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) == 0, "SDL Error: " << SDL_GetError());

    // Position on screen
    auto positionVector = m_positionVector - Camera::getInstance().position();

    // Define points on the trap
    auto b0 = positionVector;

    auto b1 = positionVector;
    b1.x += m_width;

    auto b2 = positionVector;
    b2.x += m_width;
    b2.y += m_height;

    auto b3 = positionVector;
    b3.y += m_height;

    ZD_ASSERT(SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderDrawPoint(renderer, b0.x, b0.y) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderDrawPoint(renderer, b1.x, b1.y) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderDrawPoint(renderer, b2.x, b2.y) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderDrawPoint(renderer, b3.x, b3.y) == 0, "SDL Error: " << SDL_GetError());
    

    auto linkPositionVector = Link::getInstance().position() - Camera::getInstance().position();
    auto p0 = linkPositionVector;

    auto p1 = linkPositionVector;
    p1.x += m_width;

    auto p2 = linkPositionVector;
    p2.x += m_width;
    p2.y += m_height;

    auto p3 = linkPositionVector;
    p3.y += m_height;

    ZD_ASSERT(SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderDrawPoint(renderer, p0.x, p0.y) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderDrawPoint(renderer, p1.x, p1.y) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderDrawPoint(renderer, p2.x, p2.y) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderDrawPoint(renderer, p3.x, p3.y) == 0, "SDL Error: " << SDL_GetError());
    
    auto b2b3mid = (b2 + b3) / 2;
    ZD_ASSERT(SDL_RenderDrawPoint(renderer, b2b3mid.x, b2b3mid.y) == 0, "SDL Error: " << SDL_GetError());
    */
    
    // SDL_RenderDrawLine
}

float BladeTrap::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> BladeTrap::position() const noexcept
{
    return m_positionVector;
}

void BladeTrap::attack() noexcept
{
    // Attacks when Link comes into range by sliding range pixels out

    // Position on screen
    auto positionVector = m_positionVector - Camera::getInstance().position();

    // Define points on the trap
    auto b0 = positionVector;

    auto b1 = positionVector;
    b1.x += m_width;
    
    auto b2 = positionVector;
    b2.x += m_width;
    b2.y += m_height;

    auto b3 = positionVector;
    b3.y += m_height;

    // Link's points
    auto linkPositionVector = Link::getInstance().position() - Camera::getInstance().position();
    auto p0 = linkPositionVector;

    auto p1 = linkPositionVector;
    p1.x += m_width;

    auto p2 = linkPositionVector;
    p2.x += m_width;
    p2.y += m_height;

    auto p3 = linkPositionVector;
    p3.y += m_height;

    auto distanceToLink = (Link::getInstance().position() - m_positionVector).length();

    // Returns true if p0 is between p1 and p2
    // p1 and p2 must be co-linear
    auto pointIsBetweenPoints = [](bool horizontal, const Vector<float>& p0, const Vector<float>& p1, const Vector<float>& p2)
    {
        if (horizontal)
        {
            assert(p1.y == p2.y);
            return (p0.x >= p1.x && p0.x <= p2.x);
        }
        else
        {
            assert(p1.x == p2.x);
            return (p0.y >= p1.y && p0.y <= p2.y);
        }
    };

    if (distanceToLink < m_range && !m_attack && !m_retreat)
    {
        // Determine which pair of points Link lies between
        if ((p0.x >= b0.x) && (pointIsBetweenPoints(false, p0, b1, b2) || pointIsBetweenPoints(false, p3, b1, b2)))
        {
            // Link is right of the trap with p1 or p2 in view
            if ((p0.x >= b1.x || p3.x >= b1.x))
            {
                // Attack down
                //std::cout << "Attacking right 1\n";
                m_attack = true;
                m_directionVector = { 1,0 };
            }
            else if (pointIsBetweenPoints(false, p0, b1, b2))
            {
                // p0 is inside the trap
                // If p0 is between b1 and the midpoint of b1 and b2, then we want to attack right
                // otherwise we want to attack down
                m_attack = true;
                if (pointIsBetweenPoints(false, p0, b1, (b1 + b2) / 2))
                {
                    //std::cout << "Attacking right 2\n";
                    m_directionVector = { 1,0 };
                }
                else
                {
                    //std::cout << "Attacking down 1\n";
                    m_directionVector = { 0,1 };
                }
            }
            else if (pointIsBetweenPoints(false, p3, b1, b2))
            {
                // p3 is inside the trap
                // If p3 is between b1 and the midpoint of b1 and b2, then we want to attack down
                // otherwise we want to attack right
                m_attack = true;
                if (pointIsBetweenPoints(false, p3, b1, (b1 + b2) / 2))
                {
                    //std::cout << "Attacking up 1\n";
                    m_directionVector = { 0,-1 };
                }
                else
                {
                    //std::cout << "Attacking right 3\n";
                    m_directionVector = { 1,0 };
                }
            }
        }
        else if ((p0.y >= b0.y) && (pointIsBetweenPoints(true, p0, b3, b2) || pointIsBetweenPoints(true, p1, b3, b2)))
        {
            // If we are below the trap
            // Link is below the trap with p0 or p1 in view
            if ((p0.y >= b3.y || p1.y >= b3.y))
            {
                // Attack down
                //std::cout << "Attacking down 2\n";
                m_attack = true;
                m_directionVector = { 0,1 };
            }
            else if (pointIsBetweenPoints(true, p1, b3, b2))
            {
                // p1 is inside the trap
                // If p1 is between b3 and the midpoint of b3 and b2, then we want to attack left
                // otherwise we want to attack down
                m_attack = true;
                if (pointIsBetweenPoints(true, p1, b3, (b2 + b3) / 2))
                {
                    //std::cout << "Attacking left 1\n";
                    m_directionVector = { -1,0 };
                }
                else
                {
                    //std::cout << "Attacking down 3\n";
                    m_directionVector = { 0,1 };
                }
            }
            else if (pointIsBetweenPoints(true, p0, b3, b2))
            {
                // p0 is inside the trap
                // If p0 is between b3 and the midpoint of b3 and b2, then we want to attack down
                // otherwise we want to attack right
                m_attack = true;
                if (pointIsBetweenPoints(true, p0, b3, (b2 + b3) / 2))
                {
                    //std::cout << "Attacking down 4\n";
                    m_directionVector = { 0,1 };
                }
                else
                {
                    //std::cout << "Attacking right 4\n";
                    m_directionVector = { 1,0 };
                }
            }
        }
        else if (pointIsBetweenPoints(true, p3, b0, b1) || pointIsBetweenPoints(true, p2, b0, b1))
        {
            // Link is above the trap with p0 or p1 in view
            if (p3.y <= b0.y || p2.y <= b0.y)
            {
                // Attack up
                m_attack = true;
                //std::cout << "Attacking up 2\n";
                m_directionVector = { 0,-1 };
            }
            else if (pointIsBetweenPoints(true, p3, b0, b1))
            {
                // p0 is inside the trap
                // If p0 is between b0 and the midpoint of b0 and b1, then we want to attack left
                // otherwise we want to attack up
                m_attack = true;
                if (pointIsBetweenPoints(true, p3, b0, (b0 + b1) / 2))
                {
                    //std::cout << "Attacking up 3\n";
                    m_directionVector = { 0,-1 };
                }
                else
                {
                    //std::cout << "Attacking right 5\n";
                    m_directionVector = { 1,0 };
                }
            }
            else if (pointIsBetweenPoints(true, p2, b3, b2))
            {
                // p1 is inside the trap
                // If p1 is between b0 and the midpoint of b0 and b1, then we want to attack up
                // otherwise we want to attack right
                m_attack = true;
                if (pointIsBetweenPoints(true, p2, b0, (b0 + b1) / 2))
                {
                    //std::cout << "Attacking left 2\n";
                    m_directionVector = { -1,0 };
                }
                else
                {
                    //std::cout << "Attacking up 4\n";
                    m_directionVector = { 0,-1 };
                }
            }
        }
        else if (pointIsBetweenPoints(false,p1,b0,b3) || pointIsBetweenPoints(false, p2, b0, b3))
        {
            // Link is right of the trap with p1 or p2 in view
            if ((p1.x <= b0.x || p2.x <= b0.x))
            {
                // Attack left
                m_attack = true;
                //std::cout << "Attacking left 3\n";
                m_directionVector = { -1,0 };
            }
            else if (pointIsBetweenPoints(false, p1, b0, b3))
            {
                // p1 is inside the trap
                // If p1 is between b0 and the midpoint of b0 and b3, then we want to attack right
                // otherwise we want to attack down
                m_attack = true;
                if (pointIsBetweenPoints(false, p1, b0, (b0 + b3) / 2))
                {
                    //std::cout << "Attacking left 4\n";
                    m_directionVector = { -1,0 };
                }
                else
                {
                    //std::cout << "Attacking down 5\n";
                    m_directionVector = { 0,1 };
                }
            }
            else if (pointIsBetweenPoints(false, p2, b0, b3))
            {
                // p2 is inside the trap
                // If p2 is between b0 and the midpoint of b0 and b3, then we want to attack down
                // otherwise we want to attack right
                m_attack = true;
                if (pointIsBetweenPoints(false, p2, b0, (b0 + b3) / 2))
                {
                    //std::cout << "Attacking left 5\n";
                    m_directionVector = { -1,0 };
                }
                else
                {
                    //std::cout << "Attacking up 5\n";
                    m_directionVector = { 0,-1 };
                }
            }
        }
    }
    else if (m_attack)
    {
        // Slide out to the player
        if (m_moved < m_range)
        {
            m_positionVector += m_directionVector * m_speed;
            m_moved += m_speed;

            // Start the cooldown period
            // The current problem with the Clock object is that elapsed() will return true immediately on the first call unless reset() 
            // is called as it uses the creation time of the object to compare the time to. Must fix asap
            m_enemyTimer.reset();
        }
        else
        {
            if (m_enemyTimer.elapsed(0.75f))
            {
                m_retreat = true;
                m_attack = false;
                m_moved = 0;
            }
        }
    }
    else if (m_retreat)
    {
        if (m_moved < m_range)
        {
            m_positionVector += -m_directionVector * m_retreatSpeed;
            m_moved += m_retreatSpeed;
        }
        else
        {
            m_retreat = false;
            m_moved = 0;
        }
    }
}

void BladeTrap::die() noexcept
{
    // Can't remember if it dies or not
}

void BladeTrap::move() noexcept
{

}
