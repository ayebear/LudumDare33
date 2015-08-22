// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "collisionsystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"
#include "components.h"

CollisionSystem::CollisionSystem(es::World& world):
    world(world)
{
}

void CollisionSystem::update(float dt)
{
	// Clear collision lists
	for (auto& comp: world.getComponents<AABB>())
		comp.collisions.clear();

	// Build collision lists for all AABB components
	auto entities = world.query<AABB>();
	for (auto ent1: entities)
	{
		for (auto ent2: entities)
		{
			if (ent1.getId() != ent2.getId())
			{
				auto aabb1 = ent1.get<AABB>();
				auto aabb2 = ent2.get<AABB>();
				auto bounds1 = aabb1->getGlobalBounds(ent1.getPtr<Position>());
				auto bounds2 = aabb2->getGlobalBounds(ent2.getPtr<Position>());
				if (bounds1.intersects(bounds2))
				{
					aabb1->collisions.push_back(ent2.getId());
					aabb2->collisions.push_back(ent1.getId());
				}
			}
		}
	}
}
