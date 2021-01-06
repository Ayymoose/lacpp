#pragma once

#include "Renderable.h"
#include "Resource.h"
#include "Depth.h"
#include "Camera.h"
#include "Engine.h"

namespace Zelda
{

    // This class is for animated static objects that have no interaction with the player
    // E.g grass, torches etc

    constexpr float ANIMATED_OBJECT_FPS = 1.0f / 4.0f;

    enum class AnimatedClass
    {
        AN_TORCH,
        AN_CANDLE,
        AN_GREEN_GRASS,
        AN_BLUE_WATER,
        AN_WATER_FALL,
        AN_LAVA,
        AN_UNDERWORLD_TORCH,
        AN_ARROW_PLATFORM,
        AN_SWIVEL_DOOR,
        AN_SHALLOW_WATER_BLUE,
        AN_DEEP_WATER_BLUE
        // TODO: Add remaining
    };

    class AnimatedObject : public Renderable
    {
    public:
        // TODO: repeatAcross and repeatDown
        AnimatedObject(AnimatedClass animatedClass, int x, int y, int repeatAcross, float orientation);
        
        // Renderable overrides
        void render(SDL_Renderer* renderer) noexcept override;


        // Use variadic constructor to take positions (x,y) to construct animated tiles with one new instance 
        // instead of many
        // e.g new AnimatedObject(AnimatedClass::AN_CANDLE, 0, {16,16},{32,32},{64,64},{90,90});
        /*template<typename ...Positions>
        AnimatedObject(AnimatedClass animatedClass, float orientation, const Positions ...positions) : m_repeatAcross(0), m_positions(positions...)
        {

        }*/

    private:
        int m_repeatAcross;
        Vector<float> m_positionVector;
    };
}