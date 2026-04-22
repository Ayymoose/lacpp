#pragma once

namespace zelda::engine
{

template <typename T>
class Singleton
{
public:
    static T& instance()
    {
        static T m_instance;
        return m_instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

protected:
    Singleton() = default;
    ~Singleton() = default;
};

} // namespace zelda::engine
