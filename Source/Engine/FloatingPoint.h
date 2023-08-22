#pragma once

#include <cmath>
#include <limits>
#include <type_traits>

namespace Zelda
{
    template<typename T>
    struct FloatingPoint
    {
        static_assert(std::is_arithmetic_v<T>, "Arithemtic only type allowed");

        constexpr static bool almostEqual(T a, T b)
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

}