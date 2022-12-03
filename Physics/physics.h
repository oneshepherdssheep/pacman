#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include "../Utils/utils.h"
#include "../GameObject/game_object.h"
#include "../Map/map.h"

// Move Actions
bool PHYSICS_movePacman(TMap* map, TPacman* pacman, enum TEvent directionEvent);
bool PHYSICS_movePoint(TPoint* point, enum TEvent directionEvent);
bool PHYSICS_movePointTo(TPoint* point, const TPoint destination);
void PHYSICS_moveGhosts(TMap* map, TPacman* pacman, TGhost* ghosts, const size_t ghostCount);

// Others
void PHYSICS_updateGhostsState(const TPacman* pacman, TGhost* ghosts, const size_t ghostCount);

#endif