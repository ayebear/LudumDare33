// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "regensystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"
#include "components.h"

RegenSystem::RegenSystem(es::World& world):
    world(world)
{
}

void RegenSystem::update(float dt)
{
    for (auto ent: world.query<RadiusRegen, Radius>())
    {
        auto regen = ent.get<RadiusRegen>();
        auto radius = ent.get<Radius>();
        radius->radius += regen->amount * dt;
    }
}
