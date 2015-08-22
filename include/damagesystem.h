// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include <es/system.h>

namespace es
{
    class World;
}

class DamageSystem: public es::System
{
    public:
        DamageSystem(es::World& world);
        void update(float dt);

    private:
        es::World& world;
};

#endif
