// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <SFML/Graphics.hpp>
#include <es/system.h>

namespace es
{
    class World;
}

class MovementSystem: public es::System
{
    public:
        MovementSystem(es::World& world);
        void update(float dt);

    private:
    	sf::Vector2f calculatePosition(const sf::Vector2f& start, const sf::Vector2f& end, float speed, float dt) const;

        es::World& world;
};

#endif
