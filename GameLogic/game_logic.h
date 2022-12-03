#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../Map/map.h"

enum EPartyStatus
{
    PARTY_ONGOING,
    PARTY_LOST,
    PARTY_WON
};

bool winCheck(const TMap* map);
bool loseCheck(const TPacman pacman, const TGhost ghosts[], const size_t ghostCount);
void printWinMessage();
void printLoseMessage();

#endif