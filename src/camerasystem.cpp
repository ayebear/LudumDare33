// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "camerasystem.h"
#include <es/world.h>
#include <SFML/Window.hpp>
#include "nage/actions/actionhandler.h"

CameraSystem::CameraSystem(es::World& world, sf::RenderWindow& window, sf::View& gameView, ng::ActionHandler& actions):
    world(world),
    window(window),
    gameView(gameView),
    actions(actions)
{
}

void CameraSystem::update(float dt)
{
    if (actions["zoomIn"].isActive())
        gameView.zoom(1.0f / (1.0f + dt));
    if (actions["zoomOut"].isActive())
        gameView.zoom(1.0f + dt);
}
