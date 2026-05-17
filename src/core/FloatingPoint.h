#pragma once

#include <cmath>
#include <limits>
#include <type_traits>

namespace zelda::engine
{
template <typename T> requires std::is_arithmetic_v<T>
struct FloatingPoint
{
    constexpr static bool equal(T a, T b)
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return std::fabs(a - b) < std::numeric_limits<T>::epsilon();
        }
        else
        {
            return a == b;
        }
    }
};

} // namespace zelda::engine