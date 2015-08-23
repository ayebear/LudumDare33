// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <SFML/Graphics.hpp>
#include "es/system.h"

namespace es
{
    class World;
}

namespace sf
{
    class RenderWindow;
    class View;
}

namespace ng
{
    class ActionHandler;
}

/*
This system handles automatic and manual control of the game view.
*/
class CameraSystem: public es::System
{
    public:
        CameraSystem(es::World& world, sf::RenderWindow& window, sf::View& gameView, ng::ActionHandler& actions);
        void update(float dt);

    private:
        es::World& world;
        sf::RenderWindow& window;
        sf::View& gameView;
        ng::ActionHandler& actions;
        float zoomLevel{1.0f};
};

#endif
