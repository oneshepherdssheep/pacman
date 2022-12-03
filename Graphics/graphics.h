#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../Map/map.h"
#include "../GameObject/game_object.h"

void GRAPHICS_draw(TMap* map, const TPacman pacman, const TGhost* ghosts);

#endif