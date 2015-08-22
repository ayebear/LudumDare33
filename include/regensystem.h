// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef REGENSYSTEM_H
#define REGENSYSTEM_H

#include <SFML/Graphics.hpp>
#include <es/system.h>

namespace es
{
    class World;
}

class RegenSystem: public es::System
{
    public:
        RegenSystem(es::World& world);
        void update(float dt);

    private:
        es::World& world;
};

#endif
