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
    for (auto& event: es::Events::get<MousePosEvent>())
        currentMousePos = event.mousePos;

    // Handle right-click for selected entities, and setup destinations
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        std::vector<es::Entity> selectedEnts;
        for (auto ent: world.query<Selectable>())
        {
            if (ent.get<Selectable>()->selected)
                selectedEnts.push_back(ent);
        }
        if (!selectedEnts.empty())
        {
            // Calculate grid size from entity size + padding, and number of entities
            float entSize = 100.0f;
            auto radiusComp = selectedEnts.front().get<Radius>();
            if (radiusComp)
                entSize = radiusComp->radius * 2 + 8; // Total size + padding
            unsigned gridSize = ceil(sqrt(static_cast<double>(selectedEnts.size())));
            float offset = -(((gridSize * entSize) / 2) - (entSize / 2));

            // Setup destination points as a grid
            size_t index = 0;
            for (unsigned y = 0; index < selectedEnts.size() && y < gridSize; ++y)
            {
                for (unsigned x = 0; index < selectedEnts.size() && x < gridSize; ++x)
                {
                    selectedEnts[index].assign<Destination>(currentMousePos.x + (x * entSize) + offset,
                                                            currentMousePos.y + (y * entSize) + offset);
                    ++index;
                }
            }
        }
    }
}
