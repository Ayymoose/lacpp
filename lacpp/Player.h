#ifndef PLAYER_H
#define PLAYER_H

#include "Renderable.h"
#include "Controllable.h"
#include "Vec2.h"
#include "Character.h"

#include "Camera.h"
#include "Timer.h"

class Player : public Controllable, public Renderable, public Character
{
public:
    Player();
    ~Player();
    void render(SDL_Renderer* pRenderer);
    void control();

    void attack();
    void die();
    Vec2 position() const
    {
        return m_position;
    }

    void add(int x, int y)
    {
        m_position.add(x, y);
    }

    void trackedBy(Camera* camera)
    {
        m_camera = camera;
    }

private:
    Vec2 m_jumpVector;

    Camera* m_camera;

    unsigned int currentTicks;
    int currentFrame;
    int max_frame;
    int speed;

};


#endif // !PLAYER_H
