// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "movetosystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"
#include "components.h"

MoveToSystem::MoveToSystem(es::World& world):
    world(world)
{
}

void MoveToSystem::update(float dt)
{
    // Handle right-click for selected entities, and setup destinations
    for (auto& event: es::Events::get<MouseClickedEvent>())
    {
        if (event.button == sf::Mouse::Right)
        {
            for (auto ent: world.query<Selectable>())
            {
                if (ent.get<Selectable>()->selected)
                    ent.assign<Destination>(event.mousePos.x, event.mousePos.y);
            }
        }
    }
}
