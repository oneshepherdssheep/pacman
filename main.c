#include <stdio.h>
#include "Map/map.h"
#include "Input/input.h"
#include "Graphics/graphics.h"
#include "GameObject/game_object.h"
#include "Physics/physics.h"
#include "GameLogic/game_logic.h"

// Game Data Set

TMap* map_g;
TPacman pacman_g = {0, 0,NONE};
TGhost ghosts_g[2] = {
        {0,0,NORMAL},
        {0,0,NORMAL}
};

//

void initPacman(TMap* map,TPacman* pacman)
{
    TPoint point = getPacmanInitialPosition(map);
    pacman->position.x = point.x;
    pacman->position.y = point.y;
    printf("Pacman (%d,%d)\n", pacman->position.x, pacman->position.y);
}

void initGhosts(TMap* map,TGhost ghosts[2],const size_t ghostCount)
{
    // Ghosts
    for(size_t index = 0; index < ghostCount;index++)
    {
        TPoint point = getGhostInitialPosition(map,index);
        ghosts[index].point.x = point.x;
        ghosts[index].point.y = point.y;
        printf("Ghost  (%d,%d)\n", ghosts[index].point.x, ghosts[index].point.y);
    }
}

//

void gameInit()
{
    printf("Pacman");
    // Init
    map_g = (TMap*) malloc(sizeof(TMap));
    loadMap(map_g);
    if(isMapValid(map_g))
    {
        initPacman(map_g, &pacman_g);
        initGhosts(map_g,ghosts_g,sizeof(ghosts_g)/sizeof(ghosts_g[0]));
        removeMoveableElement(map_g);
        printf("[pacman] valid map_g loaded.\n");
        draw(map_g,pacman_g,ghosts_g);
    }
    else
    {
        printf("[pacman_g] map_g loaded is invalid!\n");
    }
}

void gameLoop()
{
    bool partyFinished = false;
    enum EPartyStatus partyStatus = PARTY_ONGOING;
    enum TEvent event;
    size_t ghostCount = sizeof(ghosts_g)/sizeof(ghosts_g[0]);

    do{
        event = getLastUserInputEvent();
        if(isEventAMove(event) && !partyFinished)
        {
            // Pacman Physics
            movePacman(map_g,&pacman_g,event);
            removeFoodElement(map_g, pacman_g.position.x, pacman_g.position.y);
            // Game Logic most priority for Pacman (Win counted first than Loss)
            if(isGameWon(map_g))
            {
                partyStatus = PARTY_WON;
                partyFinished = true;
            }
            else if(isGameLost(pacman_g,ghosts_g,ghostCount))
            {
                partyStatus = PARTY_LOST;
                partyFinished = true;
            }
            else
            {
                // Ghosts Physics
                moveGhosts(map_g,&pacman_g,ghosts_g,ghostCount);
                updateGhostsState(&pacman_g,ghosts_g,ghostCount);
                // Game Logic less priority for Ghosts
                if(isGameLost(pacman_g,ghosts_g,ghostCount))
                {
                    partyStatus = PARTY_LOST;
                    partyFinished = true;
                }
            }
            // Graphics for all
            draw(map_g,pacman_g,ghosts_g);
        }
        else if(partyFinished)
        {
            // nothing to do
            if(partyStatus == PARTY_WON)
            {
                printWinMessage();
            }
            else if(partyStatus == PARTY_LOST)
            {
                printLoseMessage();
            }
            else
            {
                // Nothing to do (shouldn't happen)
            }
            getLastUserInputEvent();
            event = EXIT;
        }
        else
        {
            // Nothing to do
        }
    } while(event!= EXIT);


}

void gameExit()
{
    free(map_g);
}

int main()
{
    gameInit();
    gameLoop();
    gameExit();
    return 0;
}
