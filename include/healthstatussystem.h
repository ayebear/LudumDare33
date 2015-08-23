// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef HEALTHSTATUSSYSTEM_H
#define HEALTHSTATUSSYSTEM_H

#include <es/system.h>

namespace es
{
    class World;
    class Entity;
}

/*
Updates colors of entities based on their health components.
*/
class HealthStatusSystem: public es::System
{
    public:
        HealthStatusSystem(es::World& world);
        void update(float dt);

    private:
        es::World& world;
};

#endif
