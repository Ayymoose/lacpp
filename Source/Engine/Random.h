#pragma once

#include <random>
#include <cassert>

namespace Zelda
{

struct Random
{
    // Generate a random int/float between start and end inclusive
    template <typename T>
    static T random(const int start, const int end)
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

    // Choose a random argument from a given list of items
    template <typename T, typename... Args>
    static T choose(T arg, Args... args)
    { 
        static_assert(sizeof...(Args) > 0);
        constexpr auto size = 1 + sizeof...(Args);
        T arr[size] = { 0 };

        int i = 0;
        // Don't forget the first arg

        arr[i++] = arg;
        // Fold using comma operator
        (void(arr[i++] = args) , ...);

        // Return a random index
        return arr[random<int>(0, size - 1)];
    }

};

}