// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef BOUNDSSYSTEM_H
#define BOUNDSSYSTEM_H

#include <es/system.h>

namespace es
{
    class World;
    class Entity;
}

/*
Checks the outer bounds of the game, and ensures entities do not pass it.
Also changes the velocity of entities that hit the sides, so they "bounce" off.
*/
class BoundsSystem: public es::System
{
    public:
        BoundsSystem(es::World& world);
        void update(float dt);

    private:
        es::World& world;
};

#endif
