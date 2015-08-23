// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "selectionboxsystem.h"
#include <es/events.h>
#include <es/world.h>
#include "gameevents.h"
#include "components.h"
#include <iostream>

SelectionBoxSystem::SelectionBoxSystem(es::World& world):
    world(world)
{
}

void SelectionBoxSystem::update(float dt)
{
    // Handle mouse input for creating selection box
    if (selecting)
    {
        // Update corner position
        for (auto& event: es::Events::get<MousePosEvent>())
            updatePos(event.mousePos);

        // Stop selecting and update corner position
        for (auto& event: es::Events::get<MouseReleasedEvent>())
        {
            if (event.button == sf::Mouse::Left)
            {
                auto selBoxAabb = world.get("selBox").get<AABB>();
                if (selBoxAabb)
                {
                    auto& rect = selBoxAabb->rect;
                    std::cout << "FINISH: " << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << "\n";
                }
                selecting = false;
                world.destroy("selBox");
            }
        }
    }
    else
    {
        if (!es::Events::exists<MouseReleasedEvent>())
        {
            for (auto& event: es::Events::get<MouseClickedEvent>())
            {
                if (event.button == sf::Mouse::Left)
                {
                    selecting = true;
                    startPos(event.mousePos);
                }
            }
        }
    }
}

void SelectionBoxSystem::updatePos(const sf::Vector2f& pos)
{
    auto selBox = world.get("selBox");
    if (selBox)
    {
        auto selBoxPos = selBox.get<Position>();
        auto selBoxSize = selBox.get<Size>();
        if (selBoxPos && selBoxSize)
        {
            selBoxSize->x = pos.x - selBoxPos->x;
            selBoxSize->y = pos.y - selBoxPos->y;
            // std::cout << selBoxSize->x << ", " << selBoxSize->y << "\n";

            auto selBoxAabb = selBox.get<AABB>();
            if (selBoxAabb)
            {
                auto& rect = selBoxAabb->rect;
                rect.width = selBoxSize->x;
                rect.height = selBoxSize->y;
            }
        }
    }
}

void SelectionBoxSystem::startPos(const sf::Vector2f& pos)
{
    auto selBox = world("SelectionBox", "selBox");
    auto selBoxPos = selBox.get<Position>();
    if (selBoxPos)
    {
        selBoxPos->x = pos.x;
        selBoxPos->y = pos.y;
        std::cout << "START: " << selBoxPos->x << ", " << selBoxPos->y << "\n";
    }
    auto selBoxSize = selBox.get<Size>();
    if (selBoxSize)
    {
        selBoxSize->x = 1;
        selBoxSize->y = 1;
    }
    auto selBoxAabb = selBox.get<AABB>();
    if (selBoxAabb)
    {
        auto& rect = selBoxAabb->rect;
        rect.left = 0;
        rect.top = 0;
        rect.width = 1;
        rect.height = 1;
    }
}
