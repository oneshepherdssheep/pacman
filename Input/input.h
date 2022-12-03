#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "colours.h"
#include "../Utils/utils.h"

/**
 * @brief Type w to go UP
 */
#define UP 'w'

/**
 * @brief Type a to go LEFT
 */
#define LEFT 'a'

/**
 * @brief Type S to go DOWN
 */
#define DOWN 's'

/**
 * @brief Type d to go RIGHT
 */
#define RIGHT 'd'

/**
 * @brief Type Q to quit the game
 */
 #define QUIT 'Q'

/**
 * @brief Check if an Event is considered as a move event (event to move a in game pacman/ghost)
 * @param event : the event whose type we want to determine
 * @return true if the event is a move event, false otherwise
 */
bool INPUT_isEventAMove(enum EEvent event);

/**
 * @brief Get the last input typed by the user during the party
 * @return the last input typed by the user
 */
enum EEvent INPUT_getLastUserInputEvent();

#endif