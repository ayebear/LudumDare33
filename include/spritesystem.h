// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef SPRITESYSTEM_H
#define SPRITESYSTEM_H

#include <SFML/Graphics.hpp>
#include <es/system.h>

namespace es
{
    class World;
}

class SpriteSystem: public es::System
{
    public:
        SpriteSystem(es::World& world);
        void update(float dt);

    private:
        es::World& world;
};

#endif
