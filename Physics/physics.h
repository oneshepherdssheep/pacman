#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include "../Utils/utils.h"
#include "../GameObject/game_object.h"
#include "../Map/map.h"

/**
 * @brief Move the pacman on the map according the to the indicated direction
 * @param map : the map of the current game
 * @param pacman : the pacman to move
 * @param directionEvent : the direction to move the pacman to move to
 * @return true if the pacman has been moved, false otherwise
 */
bool PHYSICS_movePacman(TMap* map, TPacman* pacman, enum EEvent directionEvent);

/**
 * @brief Move a point to another location according to the indicated direction
 * @param point : the point to move
 * @param directionEvent : the direction to move the point to
 * @return true if the point was moved, false otherwise
 */
bool PHYSICS_movePoint(TPoint* point, enum EEvent directionEvent);

/**
 * @brief Move a point to another location according to the indicated destination point
 * @param point : the point to move
 * @param destination : the destination to move the point to
 * @return true if the point was moved, false otherwise
 */
bool PHYSICS_movePointTo(TPoint* point, const TPoint destination);

/**
 * @brief Move the ghosts to another location according to the in-game 'AI' controlling them
 * @param map : the map on which the ghosts are moving during the game
 * @param pacman : the pacman that is present in the current game
 * @param ghosts : the ghosts to move around
 * @param ghostCount : the number of ghosts present during the game
 * @return true if the ghosts are moved, false otherwise
 */
bool PHYSICS_moveGhosts(TMap* map, TPacman* pacman, TGhost* ghosts, const size_t ghostCount);

#endif