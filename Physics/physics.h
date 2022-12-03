#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include "../Utils/utils.h"
#include "../GameObject/game_object.h"
#include "../Map/map.h"

// Move Actions
bool movePacman(TMap* map,TPacman* pacman, enum TEvent directionEvent);
bool movePoint(TPoint* point,enum TEvent directionEvent);
bool movePointTo(TPoint* point,const TPoint destination);
void moveGhosts(TMap* map,TPacman* pacman,TGhost* ghosts,const size_t ghostCount);

// Tests
void isPacmanCollideWithAFood(TMap* map,TPacman* pacman);
void isPacmanCollideWithAGhost(TMap* map,TPacman* pacman,TGhost* ghosts[2]);

// Others
void updateGhostsState(const TPacman* pacman,TGhost* ghosts,const size_t ghostCount);

#endif