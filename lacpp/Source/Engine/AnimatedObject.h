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
        AnimatedObject(AnimatedClass animatedClass, int x, int y, int repeatAcross, float orientation);
        
        // Renderable overrides
        void render(SDL_Renderer* renderer) noexcept override;

    private:
        int m_repeatAcross;
        Vector<float> m_positionVector;
    };
}