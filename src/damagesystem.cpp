// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "damagesystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"
#include "components.h"
#include <iostream>

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
            if (collidedEnt)
            {
                auto collidedPlayer = collidedEnt.get<Player>();
                if (collidedPlayer && player->id != collidedPlayer->id)
                {
                    auto health = collidedEnt.get<Health>();
                    if (health)
                    {
                        health->current -= damager->amount * dt;
                        if (health->current < 1.0f)
                        {
                            killEntity(ent, collidedEnt);
                        }
                    }

                    // Could have another damager that reduces radius
                    // auto radius = collidedEnt.get<Radius>();
                    // if (radius)
                    // {
                    //     radius->radius -= damager->amount * dt;
                    //     if (radius->radius < 50.0f)
                    //         radius->radius = 50.0f;
                    // }
                }
            }
        }
    }
}

void DamageSystem::killEntity(es::Entity& killer, es::Entity& victim)
{
    auto center = victim.get<Position>();
    if (center)
    {
        // Gather information about victim
        int numDupes = 1;
        int radius = 50;
        auto radiusComp = victim.get<Radius>();
        if (radiusComp)
        {
            radius = radiusComp->radius;
            numDupes = radius / 50;
            if (numDupes < 1)
                numDupes = 1;
            if (radius < 50)
                radius = 50;
        }

        // Duplicate killer
        srand(time(nullptr));
        for (int i = 0; i < numDupes; ++i)
        {
            auto dupe = killer.clone();
            float offsetX = rand() % radius - (radius / 2);
            float offsetY = rand() % radius - (radius / 2);
            dupe.assign<Position>(center->x + offsetX, center->y + offsetY);
            dupe.remove<Destination>();
            auto sel = dupe.get<Selectable>();
            if (sel)
                sel->reset();
        }
    }

    // Remove victim (later this could be a fading animation or explosion)
    victim.destroy();
}
