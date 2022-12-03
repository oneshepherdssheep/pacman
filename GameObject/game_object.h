#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Utils/utils.h"

/**
 * @brief Enum representing the two possible state of a ghost
 */
enum EGhostState
{
    NORMAL,
    CHASE,
};

/**
 * @brief Struct representing unmovable in game object (food,walls in our cases)
 */
typedef struct
{
    const size_t x;
    const size_t y;

} TUnMovableGameObject;

/**
 * @brief Struct representing the pacman controlled by the player during the game
 */
typedef struct
{
    TPoint position;
    TPoint lastPosition;
} TPacman;

/**
 * @brief Struct representing a ghost controlled by the AI during the game
 */
typedef struct
{
    TPoint position;
    enum EGhostState state;
    enum EEvent lastDirection;
} TGhost;

/**
 * @brief Redefining TWall as an TUnMovableGameObject
 */
typedef TUnMovableGameObject TWall;

#endif