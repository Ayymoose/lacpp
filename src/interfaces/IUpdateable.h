#pragma once

namespace zelda
{
class IUpdateable
{
public:
    virtual ~IUpdateable() = default;
    virtual void update() = 0;
    IUpdateable() = default;
};

}  // namespace zelda