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
        if (radius && circle)
            circle->shape.setRadius(radius->radius);
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
