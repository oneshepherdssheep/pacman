#include "graphics.h"
#include <string.h>

void draw(TMap* map,const TPacman pacman, const TGhost* ghosts)
{
    // copy map to insert movable element
    TMap* drawnMap = (TMap*)malloc(sizeof(TMap));
    memcpy(drawnMap,map,sizeof(TMap));
    // insert element
    insertMoveableElement(drawnMap,pacman,ghosts);
    // draw
    printf("\n");
    printf("%s",(*drawnMap)[0]);
    // free
    free(drawnMap);
}
