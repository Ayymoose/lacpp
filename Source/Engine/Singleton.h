#pragma once

namespace Zelda
{
    template <typename T>
    class Singleton
    {
    public:
        static T& getInstance()
        {
            static T m_instance;
            return m_instance;
        }

    protected:
        // No Copying
        Singleton(const Singleton&) = delete;
        // No assigning
        Singleton& operator=(const Singleton&) = delete;
        // No moving
        Singleton(Singleton&&) = delete;
        // No move assigning
        Singleton& operator=(Singleton&&) = delete;

        Singleton() = default;
        virtual ~Singleton() = default;
    };
}