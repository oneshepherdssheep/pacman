#include <stdio.h>
#include "Map/map.h"
#include "Input/input.h"
#include "Graphics/graphics.h"
#include "GameObject/game_object.h"
#include "Physics/physics.h"
#include "GameLogic/game_logic.h"

//----------------------------------------------------------//
//                  GLOBAL DATA SET
//----------------------------------------------------------//

/**
 * @brief The current in game map
 */
TMap* map_g;

/**
 * @brief The current in game pacman
 */
TPacman pacman_g = {0, 0,NONE};

/**
 * @brief The current in game ghosts
 */
TGhost ghosts_g[2] = {
        {0,0,NORMAL},
        {0,0,NORMAL}
};

//----------------------------------------------------------//
//                  FUNCTIONS / PROCEDURES
//----------------------------------------------------------//


/**
 * @brief Initialize the pacman
 * @param map : the current in-game map
 * @param pacman : the played pacman
 */
void initPacman(TMap* map,TPacman* pacman)
{
    TPoint point = MAP_getPacmanInitialPosition(map);
    pacman->position.x = point.x;
    pacman->position.y = point.y;
    printf("Pacman (%d,%d)\n", pacman->position.x, pacman->position.y);
}

/**
 * @brief Method to initalize the ghosts
 * @param map : the current in game map
 * @param ghosts : the ghosts present during the game
 * @param ghostCount : the number of ghosts
 */
void initGhosts(TMap* map,TGhost ghosts[2],const size_t ghostCount)
{
    // Ghosts
    for(size_t index = 0; index < ghostCount;index++)
    {
        TPoint point = MAP_getGhostInitialPosition(map, index);
        ghosts[index].position.x = point.x;
        ghosts[index].position.y = point.y;
        printf("Ghost  (%d,%d)\n", ghosts[index].position.x, ghosts[index].position.y);
    }
}


/**
 * @brief Method to initialize the game
 * @return true if the game was properly initialized, false otherwise
 */
bool gameInit()
{
    bool gameReady;
    printf("Pacman");
    // Init
    map_g = (TMap*) malloc(sizeof(TMap));
    MAP_loadMap(map_g);
    if(MAP_isMapValid(map_g))
    {
        initPacman(map_g, &pacman_g);
        initGhosts(map_g,ghosts_g,sizeof(ghosts_g)/sizeof(ghosts_g[0]));
        MAP_removeMovableElement(map_g);
        printf("[pacman] valid map_g loaded.\n");
        GRAPHICS_draw(map_g, pacman_g, ghosts_g);
        gameReady = true;
    }
    else
    {
        printf("[pacman_g] map_g loaded is invalid!\n");
        gameReady = false;
    }
    return gameReady;
}

/**
 * @brief Main in-game loop handling the different component of the game:
 *        - physics
 *        - graphics
 *        - logic
 *        - AI
 *        - etc.
 */
void gameLoop()
{
    bool partyFinished = false;
    enum EPartyStatus partyStatus = PARTY_ONGOING;
    enum EEvent event;
    size_t ghostCount = sizeof(ghosts_g)/sizeof(ghosts_g[0]);

    do{
        //// INPUTS
        event = INPUT_getLastUserInputEvent();
        if(INPUT_isEventAMove(event) && !partyFinished)
        {
            //// PHYSICS
            // Pacman Physics
            PHYSICS_movePacman(map_g, &pacman_g, event);
            MAP_removeFoodElement(map_g, pacman_g.position.x, pacman_g.position.y);
            // Ghosts Physics
            PHYSICS_moveGhosts(map_g, &pacman_g, ghosts_g, ghostCount);
            PHYSICS_updateGhostsState(&pacman_g, ghosts_g, ghostCount);
            //// GAME LOGIC
            // Game Logic most priority for Pacman (Win counted first than Loss)
            if(GAMELOGIC_winCheck(map_g))
            {
                partyStatus = PARTY_WON;
                partyFinished = true;
            }
            else if(GAMELOGIC_loseCheck(pacman_g, ghosts_g, ghostCount))
            {
                partyStatus = PARTY_LOST;
                partyFinished = true;
            }
            else
            {
                // Nothing to do
            }
            //// GRAPHICS
            GRAPHICS_draw(map_g, pacman_g, ghosts_g);
        }

        //// GAME LOGIC WINNING and LOSING CHECKS
        if(partyFinished)
        {
            // nothing to do
            if(partyStatus == PARTY_WON)
            {
                GAMELOGIC_printWinMessage();
            }
            else if(partyStatus == PARTY_LOST)
            {
                GAMELOGIC_printLoseMessage();
            }
            else
            {
                // Nothing to do (shouldn't happen)
            }
            INPUT_getLastUserInputEvent();
            event = EXIT;
        }
        else
        {
            // Nothing to do
        }
    } while(event!= EXIT);


}

/**
 * @brief Method called when terminating the game
 *        The goal is to free all resources properly during this phase
 */
void gameExit()
{
    free(map_g);
}

int main()
{
    if(gameInit())
    {
        gameLoop();
    }
    gameExit();

    return 0;
}
