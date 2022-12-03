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

void GAMELOGIC_printWinMessage()
{
    printf("Congratulations! You win!\nPress any key to exit the game.\n");
}


void GAMELOGIC_printLoseMessage()
{
    printf("Sorry, you lose.\nPress any key to exit the game\n");
}