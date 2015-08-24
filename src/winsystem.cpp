// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#include "winsystem.h"
#include <es/world.h>
#include "components.h"
#include <iostream>

WinSystem::WinSystem(es::World& world):
    world(world)
{
}

void WinSystem::update(float dt)
{
    // Scan for different player IDs (if all are the same, that player ID won)
    int previousId = -1;
    bool winDetected = true;
    for (auto ent: world.query<Player>())
    {
        int currentId = ent.get<Player>()->id;
        if (previousId == -1)
            previousId = currentId;
        else if (previousId != currentId)
        {
            winDetected = false;
            break;
        }
    }
    if (winDetected)
        triggerWin(previousId);
}

void WinSystem::triggerWin(int playerId)
{
    const char* winners[] = {"ShowWinnerViruses", "ShowWinnerCells"};
    if (playerId >= 0 && playerId <= 1)
        world(winners[playerId], "winner");
}
