#pragma once

namespace zelda::engine
{
class Updateable
{
public:
    virtual ~Updateable() = default;

    virtual void update() = 0;
};

} // namespace zelda::engine