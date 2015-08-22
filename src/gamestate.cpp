// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "gamestate.h"
#include "gameresources.h"
#include "components.h"
#include <es/events.h>
#include <es/entityprototypeloader.h>
#include <SFML/Graphics.hpp>

GameState::GameState(GameResources& resources):
    resources(resources),
    gameInstance(resources.window)
{
    // Register components and load entity prototypes
    es::registerComponents<Position, Velocity, Size, AABB, CBA, Sprite, CircleShape, RectangleShape, Selectable, Radius, Health, Damager, Speed, RadiusRegen, Player, Destination, Selector>();
    if (!es::loadPrototypes("data/config/entities.cfg"))
        std::cerr << "ERROR: Could not load entity prototypes.\n";

    auto ent = gameInstance.world.clone("Virus");
    auto pos = ent.get<Position>();
    if (pos)
    {
        pos->x = 800;
        pos->y = 450;
    }


    auto ent2 = gameInstance.world.clone("Virus");
    pos = ent2.get<Position>();
    if (pos)
    {
        pos->x = 900;
        pos->y = 450;
    }
    auto ent3 = gameInstance.world.clone("Virus");
    pos = ent3.get<Position>();
    if (pos)
    {
        pos->x = 800;
        pos->y = 550;
    }
    auto ent4 = gameInstance.world.clone("Virus");
    pos = ent4.get<Position>();
    if (pos)
    {
        pos->x = 900;
        pos->y = 550;
    }

    gameInstance.world.clone("Cell");
}

void GameState::onStart()
{
    gameInstance.systems.initializeAll();
}

void GameState::handleEvents()
{
    for (auto& event: es::Events::get<sf::Event>())
    {
        if (event.type == sf::Event::Closed)
            stateEvent.command = ng::StateEvent::Exit;
    }
}

void GameState::update()
{
    // Update all of the systems
    gameInstance.systems.updateAll(dt);
}
