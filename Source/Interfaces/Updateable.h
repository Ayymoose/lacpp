#pragma once

#include <cassert>
#include "Vector.h"

namespace Zelda
{

class Updateable
{
public:
    virtual ~Updateable() = default;
    virtual void update() noexcept = 0;
    Updateable() = default;
protected:
    static constexpr double m_dt = 1000.0 / (double)60;
	static constexpr double m_maxFrameTime = 60;
	
    long long m_currentTime = 0;
    double m_accumulator = 0;
    
    double m_alphaTime = 0;
    Vector<float> m_lerpPrevious;
    Vector<float> m_drawPosition;
};

}