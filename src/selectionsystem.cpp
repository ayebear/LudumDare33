// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "selectionsystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"

SelectionSystem::SelectionSystem(es::World& world):
    world(world)
{
}

void SelectionSystem::update(float dt)
{
    // Handle mouse input for creating selection box

    // Handle collisions with selection box (set selectable flags, and add entities for drawing selection areas)
}
