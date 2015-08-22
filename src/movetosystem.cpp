// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "movetosystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"

MoveToSystem::MoveToSystem(es::World& world):
    world(world)
{
}

void MoveToSystem::update(float dt)
{
    // Handle right-click for selected entities, and setup paths
}
