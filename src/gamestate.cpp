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
    es::registerComponents<Position, Velocity, Size, AABB, CBA, Sprite, CircleShape, RectangleShape, Selectable, Radius, Health, Damager, Speed, RadiusRegen, Player, Destination, ZIndex, Selector>();
    if (!es::loadPrototypes("data/config/entities.cfg"))
        std::cerr << "ERROR: Could not load entity prototypes.\n";

    for (int y = 100; y <= 900; y += 600)
    {
        for (int x = 100; x <= 1600; x += 1300)
        {
            auto ent = gameInstance.world.clone("Cell");
            ent.assign<Position>(x, y);
        }
    }

    // auto ent = gameInstance.world.clone("Virus");
    // ent.assign<Position>(800, 450);

    for (int x = 0; x < 25; ++x)
    {
        auto ent = gameInstance.world.clone("Virus");
        ent.assign<Position>(800, 450);
    }
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
