#include "graphics.h"
#include <string.h>

bool GRAPHICS_draw(TMap* map, const TPacman pacman, const TGhost* ghosts)
{
    bool done = false;
    if(map!=NULL)
    {
        // copy map to insert movable element
        TMap* drawnMap = (TMap*)malloc(sizeof(TMap));
        memcpy(drawnMap,map,sizeof(TMap));
        // insert element
        MAP_insertMovableElement(drawnMap, pacman, ghosts);
        // GRAPHICS_draw
        printf("\n");
        printf("%s",(*drawnMap)[0]);
        // free
        free(drawnMap);
        done = true;
    }
    else
    {
        // Nothing to do
    }
    return done;
}


void GRAPHICS_printWinMessage()
{
    printf("Congratulations! You win!\nPress any key to exit the game.\n");
}


void GRAPHICS_printLoseMessage()
{
    printf("Sorry, you lose.\nPress any key to exit the game\n");
}

