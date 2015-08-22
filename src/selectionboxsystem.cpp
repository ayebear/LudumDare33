// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "selectionboxsystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"

SelectionBoxSystem::SelectionBoxSystem(es::World& world):
    world(world)
{
}

void SelectionBoxSystem::update(float dt)
{
    // Handle mouse input for creating selection box
}
