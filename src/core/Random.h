#pragma once

#include <array>
#include <cassert>
#include <concepts>
#include <random>

namespace zelda::engine
{

struct Random
{
    // Generate a random int/float between start and end inclusive
    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] static T random(const int start, const int end)
    {
        assert(start <= end);
        if constexpr (std::integral<T>)
        {
            std::uniform_int_distribution<T> distr(start, end);
            return distr(generator());
        }
        else
        {
            std::uniform_real_distribution<T> distr(start, end);
            return distr(generator());
        }
    }

    // Choose a random argument from a given list of items
    template <typename T, typename... Args>
        requires(sizeof...(Args) > 0) && (std::convertible_to<Args, T> && ...)
    [[nodiscard]] static T choose(T arg, Args... args)
    {
        const std::array<T, 1 + sizeof...(Args)> arr{arg, args...};
        return arr[random<std::size_t>(0, arr.size() - 1)];
    }

private:
    [[nodiscard]] static std::mt19937& generator()
    {
        static std::mt19937 gen{std::random_device{}()};
        return gen;
    }
};

} // namespace zelda::engine
