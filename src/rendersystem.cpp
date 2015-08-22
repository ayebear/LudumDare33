// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "rendersystem.h"
#include "nage/graphics/views.h"

RenderSystem::RenderSystem(es::World& world, sf::RenderWindow& window):
    world(world),
    window(window)
{
}

void RenderSystem::initialize()
{
}

void RenderSystem::update(float dt)
{
    window.clear(sf::Color(128, 128, 128));

    for (auto& sprite: world.getComponents<Sprite>())
        window.draw(sprite.sprite);

    for (auto& shape: world.getComponents<CircleShape>())
        window.draw(shape.shape);

    for (auto& shape: world.getComponents<RectangleShape>())
        window.draw(shape.shape);

    // To draw selection boxes (probably should just create more entities)
    // for (auto ent: world.query<RectangleShape>())
    // {
    //     auto shape = ent.get<RectangleShape>();
    //     window.draw(shape->shape);

    //     auto sel = ent.get<Selectable>();
    //     if (sel && sel->selected)
    //     {
    //         sf::
    //     }
    // }

    window.display();
}
