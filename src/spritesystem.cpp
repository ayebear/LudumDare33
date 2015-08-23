// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "spritesystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"
#include "components.h"

SpriteSystem::SpriteSystem(es::World& world):
    world(world)
{
}

void SpriteSystem::update(float dt)
{
    // Update sprites, shapes, from position/size components
    for (auto ent: world.query())
    {
        auto sprite = ent.get<Sprite>();
        auto circle = ent.get<CircleShape>();
        auto rect = ent.get<RectangleShape>();
        auto size = ent.get<Size>();
        auto radius = ent.get<Radius>();
        auto pos = ent.get<Position>();
        auto aabb = ent.get<AABB>();
        if (radius && circle)
        {
            circle->shape.setRadius(radius->radius);
            circle->updateOriginPoint();
        }
        if (radius && circle && aabb)
        {
            auto& rect = aabb->rect;
            rect.width = 1.75 * radius->radius;
            rect.height = 1.75 * radius->radius;
            rect.left = -0.5 * rect.width;
            rect.top = -0.5 * rect.height;
            // TODO: Update AABB for rectangle shapes as well
        }
        if (size && rect)
            rect->shape.setSize(sf::Vector2f(size->x, size->y));
        if (pos)
        {
            if (circle)
                circle->shape.setPosition(pos->x, pos->y);
            if (rect)
                rect->shape.setPosition(pos->x, pos->y);
            if (sprite)
                sprite->sprite.setPosition(pos->x, pos->y);
        }
        // TODO: Set sprite size (with setScale or something)
    }
}
