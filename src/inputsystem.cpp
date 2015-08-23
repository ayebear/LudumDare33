// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "inputsystem.h"
#include "es/events.h"
#include "gameevents.h"

InputSystem::InputSystem(sf::RenderWindow& window, sf::View& gameView):
    window(window),
    gameView(gameView)
{
}

void InputSystem::update(float dt)
{
    proxyEvents();

    // Update the view if any events were sent
    // for (auto& event: es::Events::get<ViewEvent>())
    //     currentView = event.view;
    // es::Events::clear<ViewEvent>();

    sendMouseButtonEvents(gameView);
    sendMousePositionEvents(gameView);
}

void InputSystem::proxyEvents()
{
    // Proxy SFML events from window
    es::Events::clear<sf::Event>();
    sf::Event event;
    while (window.pollEvent(event))
        es::Events::send(event);
}

void InputSystem::sendMouseButtonEvents(const sf::View& view)
{
    // Check for mouse button events, and proxy mapped coordinates
    es::Events::clear<MouseClickedEvent>();
    es::Events::clear<MouseReleasedEvent>();
    for (auto& event: es::Events::get<sf::Event>())
    {
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        {
            // Map coordinates to game view coordinates
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            sf::Vector2f gameMousePos = window.mapPixelToCoords(mousePos, view);
            if (event.type == sf::Event::MouseButtonPressed)
                es::Events::send(MouseClickedEvent{event.mouseButton.button, gameMousePos});
            else
                es::Events::send(MouseReleasedEvent{event.mouseButton.button, gameMousePos});
        }
    }
}

void InputSystem::sendMousePositionEvents(const sf::View& view)
{
    // Get mouse position - if changed, then broadcast
    es::Events::clear<MousePosEvent>();
    auto newMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
    if (currentMousePos != newMousePos)
    {
        currentMousePos = newMousePos;
        es::Events::send(MousePosEvent{currentMousePos});
    }
}
