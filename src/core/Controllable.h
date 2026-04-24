#pragma once

#include <string>
#include <cassert>

// Allows an object to receive control depending on whether it is the controller or not
namespace zelda::engine
{

class Controllable
{
public:
    Controllable(const std::string& name)
        : m_controllableName(name)
    {}

    Controllable() = default;

    virtual ~Controllable() = default;

    virtual void control() = 0;

    std::string name() const
    {
        assert(!m_controllableName.empty());
        return m_controllableName;
    }

protected:
    std::string m_controllableName;
};

} // namespace zelda