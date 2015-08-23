// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include <es/system.h>

namespace es
{
    class World;
    class Entity;
}

class DamageSystem: public es::System
{
    public:
        DamageSystem(es::World& world);
        void update(float dt);

    private:
        void killEntity(es::Entity& killer, es::Entity& victim);

        es::World& world;
};

#endif
