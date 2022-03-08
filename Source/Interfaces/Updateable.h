#pragma once

namespace Zelda
{
class Updateable
{
public:
    virtual ~Updateable() = default;
    virtual void update() noexcept = 0;
    Updateable() = default;
};

}