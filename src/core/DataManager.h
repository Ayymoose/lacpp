#pragma once

#include "Singleton.h"

namespace zelda::engine
{

class DataManager : public Singleton<DataManager>
{
public:
    DataManager() = default;

    void loadData() const;

private:

    static void loadSprites();
    void loadRooms() const;

    static void loadTailCave();
};

}; // namespace zelda::engine