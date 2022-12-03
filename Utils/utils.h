#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

//
#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '

// TPoint
typedef struct {
    int x;
    int y;
} TPoint;

// TEvent
enum TEvent {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    EXIT,
    NONE,
};

bool UTILS_isDirectionEvent(enum TEvent event);
bool UTILS_isPointCloseToPoint(TPoint p1, TPoint p2);

#endif