// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef MOVETOSYSTEM_H
#define MOVETOSYSTEM_H

#include <es/system.h>
#include <SFML/System/Vector2.hpp>

namespace es
{
    class World;
}

class MoveToSystem: public es::System
{
    public:
        MoveToSystem(es::World& world);
        void update(float dt);

    private:
        es::World& world;
        sf::Vector2f currentMousePos;
};

#endif
