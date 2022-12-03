#include "ai.h"

size_t AI_rollDice(size_t numberOfFaces)
{
    size_t roll = 1;
    if(numberOfFaces!=0)
    {
        roll = 1 + rand()/((RAND_MAX+1u)/numberOfFaces); // return a number between 1 and numberOfFaces
    }
    else
    {
        // Nothing to do
    }
    return roll;
}

enum EEvent AI_getRandomAvailableDirection(const TMap *map,const TGhost ghost) {

    TDirections directions[4] = {
            {MOVE_UP,    true},
            {MOVE_DOWN,  true},
            {MOVE_LEFT,  true},
            {MOVE_RIGHT, true}
    };
    size_t directionsCount = sizeof(directions) / sizeof(directions[0]);
    size_t possibleDirectionCount = 4;
    bool canKeepSameDirection = !MAP_isWall(map, ghost.position.x, ghost.position.y, ghost.lastDirection);
    enum EEvent selectedDirection = ghost.lastDirection;

    // Debug
    //size_t directionNumber;
    //size_t count = 1;
    //
    if(map!=NULL)
    {
        // Only choose a new direction if you can't continue in the previous one
        if (!canKeepSameDirection)
        {
            // Flag impossibles directions
            for (size_t index = 0; index < directionsCount; index++)
            {
                if (MAP_isWall(map, ghost.position.x, ghost.position.y, directions[index].direction))
                {
                    directions[index].available = false;
                    possibleDirectionCount--;
                }
                else
                {
                    // Nothing to do
                }
            }
            //
            size_t directionNumber = AI_rollDice(possibleDirectionCount);
            size_t count = 1;
            for (size_t index = 0; index < directionsCount; index++)
            {
                if (directions[index].available && count == directionNumber)
                {
                    selectedDirection = directions[index].direction;
                    break;
                }
                else if (directions[index].available && count != directionNumber)
                {
                    count++;
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
    }
    else
    {
        // Nothing to do
    }
    return selectedDirection;
}
