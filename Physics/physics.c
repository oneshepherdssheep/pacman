#include "physics.h"
#include "../Map/map.h"
#include "../AI/ai.h"

bool PHYSICS_movePointTo(TPoint* point, const TPoint destination)
{
    point->x = destination.x;
    point->y = destination.y;
}

bool PHYSICS_movePoint(TPoint* point, enum EEvent directionEvent)
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



bool PHYSICS_movePacman(TMap* map, TPacman* pacman,TGhost* ghosts, const size_t ghostCount, enum EEvent directionEvent) {
    bool hasMoved = false;
    if(map!=NULL)
    {
        // Saving last position regardless of the following
        pacman->lastPosition.x = pacman->position.x;
        pacman->lastPosition.y = pacman->position.y;
        // Check if traversing ghosts
        bool traversingGhosts = false;
        for(size_t index = 0; index <ghostCount;index++)
        {
            TPoint p = {pacman->position.x,pacman->position.y};
            PHYSICS_movePoint(&p,directionEvent);
            if(UTILS_isPointEqualToPoint(p,ghosts[index].position))
            {
                traversingGhosts = true;
                break;
            }
            else
            {
                // Nothing to do
            }
        }
        // Check wall
        if (!traversingGhosts && !MAP_isWall(map, pacman->position.x, pacman->position.y, directionEvent))
        {
            hasMoved = true;
            hasMoved = PHYSICS_movePoint(&pacman->position, directionEvent);
        }
        else
        {
            // Nothing to do
        }
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
bool PHYSICS_moveGhosts(TMap* map, TPacman* pacman, TGhost* ghosts, const size_t ghostCount)
{
    bool hasMoved = false;

    if(map!=NULL && pacman!=NULL && ghosts!=NULL)
    {
        for (size_t index = 0; index < ghostCount; index++)
        {
            //// NORMAL
            if (ghosts[index].state == NORMAL)
            {
                enum EEvent nextDirection = AI_getRandomAvailableDirection(map, ghosts[index]);
                PHYSICS_movePoint(&ghosts[index].position, nextDirection);
                ghosts[index].lastDirection = nextDirection;
                hasMoved = true;
            }
            //// CHASE
            else if (ghosts[index].state == CHASE)
            {
                PHYSICS_movePointTo(&ghosts[index].position, pacman->lastPosition);
                hasMoved = true;
            }
            else
            {
                // Nothing to do
            }
        }
    }
    else
    {
        // Nothing to do
    }
    return hasMoved;
}
