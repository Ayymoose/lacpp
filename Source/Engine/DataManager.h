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

    void loadTilemaps() const noexcept;
    void loadSprites() const noexcept;
    void loadRoomLinks() const noexcept;
};

};