#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

//

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

bool isDirectionEvent(enum TEvent event);
bool isPointCloseToPoint(TPoint p1,TPoint p2);

#endif