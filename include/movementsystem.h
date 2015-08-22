// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <SFML/Graphics.hpp>
#include <es/system.h>

namespace es
{
    class World;
}

class MovementSystem: public es::System
{
    public:
        MovementSystem(es::World& world);
        void update(float dt);

    private:
        es::World& world;
};

#endif
