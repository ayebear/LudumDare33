// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SFML/Graphics.hpp>
#include "nage/graphics/spriteloader.h"
#include "es/system.h"
#include "es/world.h"
#include "components.h"

namespace ng
{
    class TileMap;
    class Camera;
}

/*
This class handles all of the drawing to the window.
*/
class RenderSystem: public es::System
{
    public:
        RenderSystem(es::World& world, sf::RenderWindow& window, sf::View& gameView);
        void initialize();
        void update(float dt);

    private:
        es::World& world;
        sf::RenderWindow& window;
        sf::View& gameView;
};

#endif
