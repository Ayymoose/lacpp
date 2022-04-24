#pragma once

#include "Singleton.h"

namespace Zelda
{

class DataManager : public Singleton<DataManager>
{
    friend class Singleton<DataManager>;
public:
    void loadData() const noexcept;
private:
    DataManager() = default;

    void loadSprites() const noexcept;
    void loadRooms() const noexcept;

};

};