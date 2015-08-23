// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef WINSYSTEM_H
#define WINSYSTEM_H

#include <es/system.h>

namespace es
{
    class World;
    class Entity;
}

class WinSystem: public es::System
{
    public:
        WinSystem(es::World& world);
        void update(float dt);

    private:
        void triggerWin(int playerId);

        es::World& world;
};

#endif
