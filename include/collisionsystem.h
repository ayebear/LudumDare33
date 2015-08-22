// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <SFML/Graphics.hpp>
#include <es/system.h>

namespace es
{
    class World;
}

class CollisionSystem: public es::System
{
    public:
        CollisionSystem(es::World& world);
        void update(float dt);

    private:
        es::World& world;
};

#endif
