#ifndef AI_H
#define AI_H

#include "../Utils/utils.h"
#include "../Map/map.h"
#include "../GameObject/game_object.h"

/**
 * @brief Struct representing the possible directions a ghosts can take when deciding the next move
 */
typedef struct
{
    enum EEvent direction;
    bool available;
} TDirections;

/**
 * @brief Roll a virtual dice whose characterized by its number of faces
 * @param numberOfFaces : the number of faces of the dice
 * @return the number obtained after rolling this dice
 */
size_t AI_rollDice(size_t numberOfFaces);

/**
 * @brief Get a random direction among those available for a particular ghost
 * @param map : the map on which the ghost is evolving
 * @param ghost : the ghost we want to get a new direction
 * @return
 */
enum EEvent AI_getRandomAvailableDirection(const TMap *map,const TGhost ghost);



#endif