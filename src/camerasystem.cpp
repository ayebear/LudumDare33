// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "camerasystem.h"
#include <es/world.h>
#include <SFML/Window.hpp>
#include "nage/actions/actionhandler.h"
#include <iostream>

CameraSystem::CameraSystem(es::World& world, sf::RenderWindow& window, sf::View& gameView, ng::ActionHandler& actions):
    world(world),
    window(window),
    gameView(gameView),
    actions(actions)
{
}

void CameraSystem::initialize()
{
    zoomLevel = 1.0f;
}

void CameraSystem::update(float dt)
{
    const float panSpeed = 600.0f * zoomLevel;
    if (actions["zoomIn"].isActive())
    {
        float zoomAmount = 1.0f / (1.0f + dt);
        zoomLevel *= zoomAmount;
        gameView.zoom(zoomAmount);
    }
    if (actions["zoomOut"].isActive())
    {
        float zoomAmount = 1.0f + dt;
        zoomLevel *= zoomAmount;
        gameView.zoom(zoomAmount);
    }
    if (actions["panLeft"].isActive())
        gameView.move(-panSpeed * dt, 0);
    if (actions["panRight"].isActive())
        gameView.move(panSpeed * dt, 0);
    if (actions["panUp"].isActive())
        gameView.move(0, -panSpeed * dt);
    if (actions["panDown"].isActive())
        gameView.move(0, panSpeed * dt);
}
