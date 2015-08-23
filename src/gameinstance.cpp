// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "gameinstance.h"

// Include systems
#include "inputsystem.h"
#include "rendersystem.h"
#include "selectionsystem.h"
#include "selectionboxsystem.h"
#include "regensystem.h"
#include "movementsystem.h"
#include "movetosystem.h"
#include "collisionsystem.h"
#include "damagesystem.h"
#include "spritesystem.h"
#include "camerasystem.h"
#include "healthstatussystem.h"
#include "winsystem.h"

GameInstance::GameInstance(sf::RenderWindow& window):
    window(window)
{
    gameView = window.getDefaultView();
    actions.loadFromConfig("data/config/controls.cfg");

    // Setup systems
    systems.add<InputSystem>(window, gameView); // Proxy SFML input events
    systems.add<SelectionBoxSystem>(world); // Create selection box entity from mouse input
    systems.add<RegenSystem>(world); // Handle regenerating health/growing cells
    systems.add<MoveToSystem>(world); // Handle right-click to move selected entities (creates paths)
    systems.add<MovementSystem>(world); // Handles moving entities (from paths/velocities)
    systems.add<CollisionSystem>(world); // Sends events when things collide
    systems.add<DamageSystem>(world); // Handles collision events and causes damage, etc.
    // systems.add<>(); // Need a system for sharing anti-bodies between cells (along with attachment components for attaching other entities)
    systems.add<HealthStatusSystem>(world); // Updates colors based on health
    systems.add<SelectionSystem>(world); // Handles collision events with selection box, creates selection entities for render system
    systems.add<SpriteSystem>(world); // Updates sf::Sprite/sf::Shape components from size/position components
    systems.add<CameraSystem>(world, window, gameView, actions); // Handles manual and automatic zooming/panning
    systems.add<WinSystem>(world); // Detects when a player wins
    systems.add<RenderSystem>(world, window, gameView); // Renders all entities
}
