// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "selectionsystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"
#include "components.h"
#include <iostream>

SelectionSystem::SelectionSystem(es::World& world):
    world(world)
{
}

void SelectionSystem::update(float dt)
{
    // Handle collisions with selection box (set selectable flags, and add entities for drawing selection areas)
    for (auto selBox: world.query<Selector>())
    {
        // Reset all selectable flags
        for (auto& comp: world.getComponents<Selectable>())
        {
            if (comp.selected)
            {
                // std::cout << "Reset " << comp.id << "\n";
                comp.selected = false;
                world.destroy(comp.id);
                comp.id = 0;
            }
        }

        // Update selectable flags and create highlighting entities
        auto aabb = selBox.get<AABB>();
        if (aabb)
        {
            for (auto id: aabb->collisions)
            {
                // TODO: Add player ID check
                auto ent = world.get(id);
                auto sel = ent.get<Selectable>();
                if (sel && !sel->selected)
                {
                    sel->selected = true;
                    auto highlighted = world.clone(sel->prototype);
                    sel->id = highlighted.getId();
                    // std::cout << "Selected " << sel->id << "\n";
                    auto pos = ent.get<Position>();
                    if (pos)
                    {
                        auto hPos = highlighted.at<Position>();
                        hPos->x = pos->x;
                        hPos->y = pos->y;
                    }
                }
            }
        }
    }

    // Update positions of highlights
    for (auto ent: world.query<Position, Selectable>())
    {
        auto sel = ent.get<Selectable>();
        if (sel->selected)
        {
            auto pos = ent.get<Position>();
            auto selEnt = world.get(sel->id);
            if (selEnt)
            {
                auto selPos = selEnt.get<Position>();
                if (selPos)
                {
                    selPos->x = pos->x;
                    selPos->y = pos->y;
                }
            }
        }
    }
}
