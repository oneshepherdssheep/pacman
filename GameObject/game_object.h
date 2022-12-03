#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Utils/utils.h"

enum TGhostState
{
    NORMAL,
    CHASE,
};

// Unmovable Game Object
typedef struct
{
    const size_t x;
    const size_t y;

} TUnMovableGameObject;

// Pacman

typedef struct
{
    TPoint position;
    TPoint lastPosition;
} TPacman;

// Ghost

typedef struct
{
    TPoint position;
    enum TGhostState state;
    enum TEvent lastDirection;
} TGhost;

// Food

typedef struct
{
    const size_t x;
    const size_t y;
    bool exist;
} TFood;

// Wall

typedef TUnMovableGameObject TWall;

#endif