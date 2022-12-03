#ifndef AI_H
#define AI_H

#include "../Utils/utils.h"
#include "../Map/map.h"
#include "../GameObject/game_object.h"

enum AILevel
{
    LEVEL_0, // Dumb
    LEVEL_1, // Has some sense
    LEVEL_2, // Genius
};

typedef struct
{
    enum TEvent direction;
    bool available;
} TDirections;

size_t rollDice(size_t numberOfFaces);
enum TEvent getDirection(const TMap *map, TGhost ghost,enum AILevel level);
enum TEvent getRandomDirection(const TMap *map,TGhost ghost);
enum TEvent getRandomAvailableDirection(const TMap *map,TGhost ghost);
enum TEvent getBestDirectionToFollowPacman(const TMap *map,TGhost ghost);



#endif