#include "game_logic.h"


bool winCheck(const TMap* map)
{
    return (getFoodCount(map)==0);
}


bool loseCheck(const TPacman pacman, const TGhost ghosts[], const size_t ghostCount)
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

void printWinMessage()
{
    printf("Congratulations! You win!\nPress any key to exit the game.\n");
}


void printLoseMessage()
{
    printf("Sorry, you lose.\nPress any key to exit the game\n");
}