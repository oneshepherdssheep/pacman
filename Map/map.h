#ifndef MAP_LOADER
#define MAP_LOADER

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../Utils/utils.h"
#include "../GameObject/game_object.h"



#define MAP_LINE_COUNT 11
// 11 characters separated by 2*8 spaces plus 1 new line character
#define MAP_COLUMN_COUNT 32
#define MAP_FILE_COLUMN_COUNT 25
#define MAP_FILE_LINE_COUNT 9

//
//
//

#define UP_DOWN_STEP 1
#define LEFT_RIGHT_STEP 3

// ------------------------------------------------------------ //
// Types
// ------------------------------------------------------------ //

typedef enum {
    MAP_OK,
    MAP_MISSING_GHOST,
    MAP_MISSING_PLAYER
} MapOperationResult ;

typedef char TMap[MAP_LINE_COUNT][MAP_COLUMN_COUNT];

struct PacmanMap {
    TMap walls;
    TMap food;
    TMap ghosts;
    TMap player;
};

// ------------------------------------------------------------ //
// set
// ------------------------------------------------------------ //

void initMap(TMap* map);
void setInSideMapValue(TMap* map, char newValue, u_int8_t newValue_x, u_int8_t newValue_y);

// ------------------------------------------------------------ //
// get
// ------------------------------------------------------------ //

const char * getMapFilePath();
TPoint getPacmanInitialPosition(TMap* map);
TPoint getGhostInitialPosition(TMap* map,size_t index);
size_t getFoodCount(TMap* map);

// ------------------------------------------------------------ //
// checker
// ------------------------------------------------------------ //

bool isMapValid(TMap* map);
bool isCharacterImportedValid(char character);
bool isCharacterMapValid(char character);
bool isElementFood(TMap* map,size_t x,size_t y);
bool isWall(TMap* map, size_t x, size_t y, enum TEvent direction);
bool isCoordinatesValid(size_t x, size_t y);
bool isCoordinatesValidForAMove(size_t x, size_t y);

// ------------------------------------------------------------ //
// others
// ------------------------------------------------------------ //

MapOperationResult loadMap(TMap* map);
void removeMoveableElement(TMap* map);
void removeFoodElement(TMap* map,size_t x,size_t y);
void insertMoveableElement(TMap* map,const TPacman pacman,const TGhost ghosts[2]);
void printMap(TMap* map);

#endif