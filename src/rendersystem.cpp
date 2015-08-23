// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "rendersystem.h"
#include "nage/graphics/views.h"
#include "components.h"
#include "textcomponent.h"
#include <map>

RenderSystem::RenderSystem(es::World& world, sf::RenderWindow& window, sf::View& gameView):
    world(world),
    window(window),
    gameView(gameView)
{
}

void RenderSystem::initialize()
{
}

void RenderSystem::update(float dt)
{
    // Build up z-index map

    std::map<int, std::vector<const sf::Drawable*>> entsToDraw;
    for (auto ent: world.query<ZIndex>())
    {
        int layer = ent.get<ZIndex>()->layer;

        // Try to get a drawable component
        const sf::Drawable* drawable = nullptr;
        if (ent.has<Sprite>())
            drawable = &(ent.get<Sprite>()->sprite);
        else if (ent.has<CircleShape>())
            drawable = &(ent.get<CircleShape>()->shape);
        else if (ent.has<RectangleShape>())
            drawable = &(ent.get<RectangleShape>()->shape);
        else if (ent.has<Text>())
            drawable = &(ent.get<Text>()->text);

        // Add pointer to the z-index map
        if (drawable)
            entsToDraw[layer].push_back(drawable);
    }


    // Draw entities in z-index order

    window.setView(gameView);

    window.clear(sf::Color(96, 96, 96));

    for (auto& layer: entsToDraw)
    {
        for (auto& drawable: layer.second)
            window.draw(*drawable);
    }

    // for (auto& sprite: world.getComponents<Sprite>())
    //     window.draw(sprite.sprite);

    // for (auto& shape: world.getComponents<CircleShape>())
    //     window.draw(shape.shape);

    // for (auto& shape: world.getComponents<RectangleShape>())
    //     window.draw(shape.shape);

    window.display();
}
