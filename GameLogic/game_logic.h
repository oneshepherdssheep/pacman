#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../Map/map.h"

/**
 * @brief Enum indicating the different stages of the party
 */
enum EPartyStatus
{
    PARTY_ONGOING,
    PARTY_LOST,
    PARTY_WON
};

/**
 * @brief Check if the winning conditions are met
 * @param map : the map of the current game
 * @return true if the winning conditions are met, false otherwise
 */
bool GAMELOGIC_winCheck(const TMap* map);

/**
 * @brief Check if the losing conditions are met
 * @param pacman : the pacman controlled by the player in the game
 * @param ghosts : the ghosts controlled by the AI in the game
 * @param ghostCount : the number of ghosts in the game
 * @return true if the losing conditions are met, false otherwise
 */
bool GAMELOGIC_loseCheck(const TPacman pacman, const TGhost ghosts[], const size_t ghostCount);

/**
 * @brief Print the winning message on the console
 */
void GAMELOGIC_printWinMessage();

/**
 * @brief Print the losing message on the console
 */
void GAMELOGIC_printLoseMessage();

/**
 * @brief Update the status of the ghosts according to their proximity with the pacman
 * @param pacman : the pacman that is targeted by the ghosts
 * @param ghosts : the ghosts whose state we want to updated
 * @param ghostCount : the number of ghosts
 * @return true if the states were updated, false otherwise
 */
bool GAMELOGIC_updateGhostsState(const TPacman* pacman, TGhost* ghosts, const size_t ghostCount);


#endif