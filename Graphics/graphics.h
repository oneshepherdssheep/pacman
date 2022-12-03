#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../Map/map.h"
#include "../GameObject/game_object.h"

/**
 * @brief Draw the Game with its pacman,ghosts,food and walls
 * @param map : the map of the current game
 * @param pacman : the pacman the player is controlling
 * @param ghosts : the ghosts that are moving around during the game
 * @return true if the drawing was performed, false otherwise
 */
bool GRAPHICS_draw(TMap* map, const TPacman pacman, const TGhost* ghosts);


/**
 * @brief Print the winning message on the console
 */
void GRAPHICS_printWinMessage();

/**
 * @brief Print the losing message on the console
 */
void GRAPHICS_printLoseMessage();

#endif