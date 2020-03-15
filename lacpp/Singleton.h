#ifndef SINGLETON_H
#define SINGLETON_H

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

    // No move assigning

    Singleton() = default;
    virtual ~Singleton() = default;
};

#endif SINGLETON_H