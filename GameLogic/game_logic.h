#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../Map/map.h"

enum EPartyStatus
{
    PARTY_ONGOING,
    PARTY_LOST,
    PARTY_WON
};

bool isGameWon(const TMap* map);
bool isGameLost(const TPacman pacman,const TGhost ghosts[],const size_t ghostCount);
void printWinMessage();
void printLoseMessage();

#endif