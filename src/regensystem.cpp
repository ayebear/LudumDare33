// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "regensystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"
#include "components.h"
#include "nage/graphics/vectors.h"
#include <iostream>

RegenSystem::RegenSystem(es::World& world):
    world(world)
{
}

void RegenSystem::update(float dt)
{
    // Update radius components
    for (auto ent: world.query<RadiusRegen, Radius>())
    {
        auto regen = ent.get<RadiusRegen>();
        auto radius = ent.get<Radius>();
        radius->radius += regen->amount * dt;
        auto splittable = ent.get<Splittable>();
        if (splittable && radius->radius >= splittable->splitAtRadius)
            handleSplit(ent);
    }

    // Update health components
    for (auto ent: world.query<HealthRegen, Health>())
    {
        auto regen = ent.get<HealthRegen>();
        auto health = ent.get<Health>();
        health->current += regen->amount * dt;
        if (health->current > health->max)
            health->current = health->max;
        else if (health->current < 1 && regen->amount < 0)
        {
            // TODO: Move this to a common area
            auto sel = ent.get<Selectable>();
            if (sel)
                world.destroy(sel->id);
            ent.destroy();
        }
    }
}

void RegenSystem::handleSplit(es::Entity& ent)
{
    std::cout << "RegenSystem::handleSplit(" << ent.getId() << ")\n";

    // Duplicate cell and antibodies, halve radius, increase max health, place into new position
    auto dupe = ent.clone();
    auto radius1 = ent.at<Radius>();
    auto radius2 = dupe.at<Radius>();
    auto splittable1 = ent.at<Splittable>();
    auto splittable2 = dupe.at<Splittable>();
    auto health1 = ent.at<Health>();
    auto health2 = dupe.at<Health>();
    // auto position1 = ent.at<Position>();
    auto position2 = dupe.at<Position>();
    float multiplier = splittable1->radiusMultiplier;

    // Halve radius
    radius1->radius = splittable1->splitAtRadius / 2.0f;
    radius2->radius = splittable2->splitAtRadius / 2.0f;

    // Setup new max radius
    splittable1->splitAtRadius *= multiplier;
    splittable2->splitAtRadius *= multiplier;

    // Increase max health
    health1->current *= multiplier;
    health1->max *= multiplier;
    health2->current *= multiplier;
    health2->max *= multiplier;

    // Set new position (anywhere near it)
    float angle = rand() % 360;
    auto vec = ng::vec::angleToVector(angle) * (radius2->radius * 3 * multiplier);
    position2->x += vec.x;
    position2->y += vec.y;
}
