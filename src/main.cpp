// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "gameresources.h"
#include "nage/states/statestack.h"
#include "gamestate.h"

int main()
{
    GameResources resources("Ludum Dare 33: The Virus");
    ng::StateStack states;
    states.add<GameState>("Game", resources);
    states.start("Game");
    return 0;
}
