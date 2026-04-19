#pragma once

#include "Singleton.h"

namespace Zelda
{

    class DataManager : public Singleton<DataManager>
    {
        friend class Singleton<DataManager>;
    public:
        void loadData() const;
    private:
        DataManager() = default;

        static void loadSprites();
        void loadRooms() const;

        static void loadTailCave();

    };

};