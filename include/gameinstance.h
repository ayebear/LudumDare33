// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "es/world.h"
#include "es/systemcontainer.h"
#include "nage/actions/actionhandler.h"
#include <SFML/Graphics/View.hpp>

class GameSaveHandler;
namespace sf
{
    class RenderWindow;
}

/*
Contains the objects used by the game state.
*/
struct GameInstance
{
    GameInstance(sf::RenderWindow& window);

    sf::RenderWindow& window;

    es::World world;
    es::SystemContainer systems;
    ng::ActionHandler actions;
    sf::View gameView;
};

#endif
