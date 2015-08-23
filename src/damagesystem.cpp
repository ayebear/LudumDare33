// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "damagesystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"
#include "components.h"

DamageSystem::DamageSystem(es::World& world):
    world(world)
{
}

void DamageSystem::update(float dt)
{
    for (auto ent: world.query<Damager, AABB, Player>())
    {
        auto damager = ent.get<Damager>();
        auto aabb = ent.get<AABB>();
        auto player = ent.get<Player>();
        for (auto collision: aabb->collisions)
        {
            auto collidedEnt = world.get(collision);
            auto collidedPlayer = collidedEnt.get<Player>();
            if (player->id != collidedPlayer->id)
            {
                auto health = collidedEnt.get<Health>();
                if (health)
                    health->current -= damager->amount * dt;

                auto radius = collidedEnt.get<Radius>();
                if (radius)
                    radius->radius -= damager->amount * dt;
            }
        }
    }
}
