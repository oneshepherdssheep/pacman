#include "physics.h"
#include "../Map/map.h"
#include "../AI/ai.h"

bool PHYSICS_movePointTo(TPoint* point, const TPoint destination)
{
    point->x = destination.x;
    point->y = destination.y;
}

bool PHYSICS_movePoint(TPoint* point, enum TEvent directionEvent)
{
    bool pointChanged = true;
    // UP
    if(directionEvent==MOVE_UP)
    {
        point->y-=UP_DOWN_STEP;
    }
        // DOWN
    else if(directionEvent==MOVE_DOWN)
    {
        point->y+=UP_DOWN_STEP;
    }
        // RIGHT
    else if(directionEvent==MOVE_RIGHT)
    {
        point->x+=LEFT_RIGHT_STEP;
    }
        // LEFT
    else if(directionEvent==MOVE_LEFT)
    {
        point->x-=LEFT_RIGHT_STEP;
    }
    else
    {
        pointChanged = false;
    }
    return pointChanged;
}


/**
 *
 * @param map
 * @param pacman
 * @param directionEvent
 */
bool PHYSICS_movePacman(TMap* map, TPacman* pacman, enum TEvent directionEvent)
{
    bool hasMoved = false;
    pacman->lastPosition.x = pacman->position.x;
    pacman->lastPosition.y = pacman->position.y;
    if(!MAP_isWall(map, pacman->position.x, pacman->position.y, directionEvent))
    {
        hasMoved = true;
        hasMoved = PHYSICS_movePoint(&pacman->position, directionEvent);
    }
    else
    {
        // Nothing to do
    }
    return hasMoved;
}

/**
 *
 * @param map
 * @param ghosts
 * @param directionEvent
 */
void PHYSICS_moveGhosts(TMap* map, TPacman* pacman, TGhost* ghosts, const size_t ghostCount)
{
    for(size_t index = 0; index < ghostCount; index++)
    {
        //// NORMAL
        if(ghosts[index].state == NORMAL)
        {
            enum TEvent nextDirection = AI_getRandomAvailableDirection(map, ghosts[index]);
            PHYSICS_movePoint(&ghosts[index].position, nextDirection);
            ghosts[index].lastDirection = nextDirection;
        }
        //// CHASE
        else if(ghosts[index].state == CHASE)
        {
            PHYSICS_movePointTo(&ghosts[index].position, pacman->lastPosition);
        }
        else
        {
            // Nothing to do
        }
    }
}

void PHYSICS_updateGhostsState(const TPacman* pacman, TGhost* ghosts, const size_t ghostCount)
{
    for(size_t index = 0; index < ghostCount; index++)
    {
        if(UTILS_isPointCloseToPoint(pacman->position, ghosts[index].position))
        {
            ghosts[index].state = CHASE;
        }
        else
        {
            ghosts[index].state = NORMAL;
        }
    }
}


bool UTILS_isPointCloseToPoint(TPoint p1, TPoint p2)
{
    // UP
    if((p1.x==p2.x) && ((p1.y-UP_DOWN_STEP)==p2.y))
    {
        return true;
    }
    // DOWN
    else if((p1.x==p2.x) && ((p1.y+UP_DOWN_STEP)==p2.y))
    {
        return true;
    }
    // RIGHT
    else if((p1.x+LEFT_RIGHT_STEP==p2.x) && ((p1.y)==p2.y))
    {
        return true;
    }
    // LEFT
    else if((p1.x-LEFT_RIGHT_STEP==p2.x) && ((p1.y)==p2.y))
    {
        return true;
    }
    else
    {
        return false;
    }
}