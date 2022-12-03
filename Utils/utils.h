#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/**
 * @brief Character 'P' stands for PACMAN
 */
#define PACMAN 'P'

/**
 * @brief Character 'G' stands for GHOST
 */
#define GHOST 'G'

/**
 * @brief Character '.' stands for DOT
 */
#define DOT '.'

/**
 * @brief Character 'W' stands for WALL
 */
#define WALL 'W'

/**
 * @brief Empty character
 */
#define EMPTY ' '

/**
 * @brief Struct representing a simple point (x,y)
 */
typedef struct {
    int x;
    int y;
} TPoint;

/**
 * @brief Enum representing all the possible events that are handled during the game
 */
enum EEvent {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    EXIT,
    NONE,
};

/**
 * @brief Check if the event is a direction event such as MOVE_UP,MOVE_DOWN,MOVE_RIGHT or MOVE_LEFT
 * @param event : the current event to analyze
 * @return true if the event is a direction event, false otherwise
 */
bool UTILS_isDirectionEvent(enum EEvent event);

/**
 * @brief Check if two points are close from one another
 * @param p1 : first point
 * @param p2 : second point
 * @return true if the two points are "closed", false otherwise
 */
bool UTILS_isPointCloseToPoint(TPoint p1, TPoint p2);

#endif