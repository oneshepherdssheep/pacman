#include "game_logic.h"


bool GAMELOGIC_winCheck(const TMap* map)
{
    return (MAP_getFoodCount(map) == 0);
}


bool GAMELOGIC_loseCheck(const TPacman pacman, const TGhost ghosts[], const size_t ghostCount)
{
    bool lost = false;
    for(size_t index = 0; index < ghostCount;index++)
    {
        if((pacman.position.x == ghosts[index].position.x) && (pacman.position.y == ghosts[index].position.y))
        {
            lost = true;
            break;
        }
    }
    return lost;
}

bool GAMELOGIC_updateGhostsState(const TPacman* pacman, TGhost* ghosts, const size_t ghostCount)
{
    bool updated=false;
    if(pacman!=NULL && ghosts!=NULL)
    {
        for (size_t index = 0; index < ghostCount; index++)
        {
            if (UTILS_isPointCloseToPoint(pacman->position, ghosts[index].position))
            {
                ghosts[index].state = CHASE;
                updated = true;
            }
            else
            {
                ghosts[index].state = NORMAL;
                updated = true;
            }
        }
    }
    else
    {
        // Nothing to do
    }
    return updated;
}
