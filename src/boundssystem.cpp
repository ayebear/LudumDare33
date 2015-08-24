// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "boundssystem.h"
#include <es/world.h>
#include "components.h"
// #include <iostream>

BoundsSystem::BoundsSystem(es::World& world):
    world(world)
{
}

void BoundsSystem::update(float dt)
{
    auto bounds = world("Boundary", "boundary");
    auto boundsPos = bounds.at<Position>();
    auto boundsRect = bounds.at<AABB>()->getGlobalBounds(boundsPos.get());
    for (auto ent: world.query<Position, Velocity>())
    {
        auto pos = ent.get<Position>();
        auto vel = ent.get<Velocity>();
        if (!boundsRect.contains(pos->x, pos->y))
        {
            vel->x *= -1;
            vel->y *= -1;
        }
    }
}
