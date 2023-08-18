#pragma once

namespace Zelda
{
    class IUpdateable
    {
    public:
        virtual ~IUpdateable() = default;
        virtual void update() = 0;
        IUpdateable() = default;
    };

}