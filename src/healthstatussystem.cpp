// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "healthstatussystem.h"
#include <es/world.h>
#include "components.h"
#include "nage/graphics/colors.h"
#include <iostream>

HealthStatusSystem::HealthStatusSystem(es::World& world):
    world(world)
{
}

void HealthStatusSystem::update(float dt)
{
    for (auto ent: world.query<Health>())
    {
        auto health = ent.get<Health>();
        float ratio = 1.0f - (health->current / health->max);

        auto circle = ent.get<CircleShape>();
        if (circle)
        {
            circle->shape.setFillColor(ng::desaturate(circle->fillColor.toColor(), ratio));
            circle->shape.setOutlineColor(ng::desaturate(circle->outlineColor.toColor(), ratio));
        }
    }
}
