#pragma once

#include <random>
#include <cassert>

namespace Zelda
{

// Generate a random int/float between start and end inclusive
template <typename T>
inline T random(const int start, const int end)
{
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Invalid template type");

    assert(start <= end);
    // Seed the generator
    std::random_device rd;
    std::mt19937 gen(rd()); 
    // Define the range
    if constexpr (std::is_integral_v<T>)
    {
        std::uniform_int_distribution<T> distr(start, end);
        return distr(gen);
    }
    else
    {
        std::uniform_real_distribution<T> distr(start, end);
        return distr(gen);
    }
}

}