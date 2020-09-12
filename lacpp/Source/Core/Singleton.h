#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

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

    Singleton()
    {
        std::cout << "Creating singleton: " << typeid(*this).name() << "\n";
    }
    virtual ~Singleton() = default;
};

#endif SINGLETON_H