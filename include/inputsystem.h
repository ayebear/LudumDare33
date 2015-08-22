// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SFML/Graphics.hpp>
#include "es/system.h"

/*
This class handles the processing of all inputs, and sends out global input events with all of the needed information.
*/
class InputSystem: public es::System
{
    public:
        InputSystem(sf::RenderWindow& window);
        void update(float dt);

    private:
        void proxyEvents();
        void sendMouseButtonEvents(const sf::View& view);
        void sendMousePositionEvents(const sf::View& view);

        sf::RenderWindow& window;
        sf::Vector2f currentMousePos;

        sf::View currentView;
};

#endif
