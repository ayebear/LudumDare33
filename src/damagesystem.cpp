// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "damagesystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"
#include "components.h"

DamageSystem::DamageSystem(es::World& world):
    world(world)
{
}

void DamageSystem::update(float dt)
{
    for (auto ent: world.query<Damager, AABB>())
    {
    	auto damager = ent.get<Damager>();
    	auto aabb = ent.get<AABB>();
    	for (auto collision: aabb->collisions)
    	{
    		auto collidedEnt = world.get(collision);
    		auto health = collidedEnt.get<Health>();
    		if (health)
    			health->current -= damager->amount * dt;

    		auto radius = collidedEnt.get<Radius>();
    		if (radius)
    			radius->radius -= damager->amount * dt;
    	}
    }
}
