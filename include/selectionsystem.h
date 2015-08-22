// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef SELECTIONSYSTEM_H
#define SELECTIONSYSTEM_H

#include <SFML/Graphics.hpp>
#include <es/system.h>

namespace es
{
    class World;
}

class SelectionSystem: public es::System
{
    public:
        SelectionSystem(es::World& world);
        void update(float dt);

    private:
        es::World& world;
};

#endif
