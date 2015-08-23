// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef SELECTIONBOXSYSTEM_H
#define SELECTIONBOXSYSTEM_H

#include <SFML/Graphics.hpp>
#include <es/system.h>

namespace es
{
    class World;
}

class SelectionBoxSystem: public es::System
{
    public:
        SelectionBoxSystem(es::World& world);
        void update(float dt);

    private:
        void updatePos(const sf::Vector2f& pos);
        void startPos(const sf::Vector2f& pos);

        es::World& world;
        bool selecting{false};
};

#endif
