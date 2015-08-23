// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "movementsystem.h"
#include <es/events.h>
#include <es/world.h>
#include "nage/graphics/vectors.h"
#include "nage/misc/utils.h"
#include "gameevents.h"
#include "components.h"
#include <iostream>

MovementSystem::MovementSystem(es::World& world):
    world(world)
{
}

void MovementSystem::update(float dt)
{
    // Update positions based on Destination components
    for (auto ent: world.query<Position, Destination, Speed>())
    {
        auto pos = ent.get<Position>();
        auto dest = ent.get<Destination>();
        auto speed = ent.get<Speed>();
        float calculatedSpeed = speed->speed;
        if (ent.has<HealthAffectsSpeed>())
        {
            auto health = ent.get<Health>();
            if (health)
                calculatedSpeed *= (health->current / health->max);
        }
        auto newPos = calculatePosition(sf::Vector2f(pos->x, pos->y), sf::Vector2f(dest->x, dest->y), calculatedSpeed, dt);
        pos->x = newPos.x;
        pos->y = newPos.y;
        // std::cout << pos->x << ", " << pos->y << "\n";
        if (ng::approxEqual(newPos.x, dest->x, 2.0f) && ng::approxEqual(newPos.y, dest->y, 2.0f))
        {
            pos->x = dest->x;
            pos->y = dest->y;
            ent.remove<Destination>();
        }
    }

    // Update positions from velocity
    for (auto ent: world.query<Position, Velocity>())
    {
        auto pos = ent.get<Position>();
        auto vel = ent.get<Velocity>();
        pos->x += vel->x * dt;
        pos->y += vel->y * dt;
    }
}

sf::Vector2f MovementSystem::calculatePosition(const sf::Vector2f& start, const sf::Vector2f& end, float speed, float dt) const
{
    auto diff = end - start;
    ng::vec::normalize(diff);
    float scale = dt * speed;
    auto pos = start;
    pos.x += diff.x * scale;
    pos.y += diff.y * scale;
    return pos;
}
