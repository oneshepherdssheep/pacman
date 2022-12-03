#ifndef MAP_LOADER
#define MAP_LOADER

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../Utils/utils.h"
#include "../GameObject/game_object.h"


#define MAP_LINE_COUNT 11           // 9 Line for the real map + 2 lines for outer wall
#define MAP_COLUMN_COUNT 32         // 11 characters separated by 2*10 spaces plus 1 new line character
#define MAP_FILE_COLUMN_COUNT 25    // 9 characters separated by 8*2 spaces
#define MAP_FILE_LINE_COUNT 9       // 9 Line for the map file

#define UP_DOWN_STEP 1              // To move UP or DOWN we only need a step of 1
#define LEFT_RIGHT_STEP 3           // To move RIGHT or LEFT we need a step of 3 due to spaces


/**
 * @brief Type representing a game map on which the game is played
 */
typedef char TMap[MAP_LINE_COUNT][MAP_COLUMN_COUNT];

/**
 * @brief Initialize the map
 *        This method will prepare an empty map with only the outer wall
 * @param map : map to initialize
 * @return true if the map was initialized, false otherwise
 */
bool MAP_initMap(TMap* map);

/**
 * @brief Set a particular element on the map
 * @param map : the map on which we want to set a particular element
 * @param newElement : the new element to add on the map
 * @param element_x : the x coordinate of the new element
 * @param element_y : the y coordinate of the new element
 * @return true if the new element was placed, false otherwise
 */
bool MAP_setInSideMapElement(TMap* map, char newElement, size_t element_x, size_t element_y);

/**
 * @brief Get the game map file location
 * @return the string representing the location of the game map
 */
const char * MAP_getMapFilePath();

/**
 * @brief Get the initial position of the pacman
 * @param map : the current in game map
 * @return TPoint representing the initial position of the pacman
 */
TPoint MAP_getPacmanInitialPosition(TMap* map);

/**
 * @brief Get the initial position of a particular ghost identified by the index
 * @param map : the current in game map
 * @param index : the index of the ghosts (starting at 0 for the 1st ghost)
 * @return TPoint representing the initial position of the indicated ghost
 */
TPoint MAP_getGhostInitialPosition(TMap* map, size_t index);

/**
 * @brief Get the number of food element left on the map
 * @param map : the current in game map
 * @return the number of food element left on the current map
 */
size_t MAP_getFoodCount(const TMap* map);

/**
 * @brief Check if the map is valid
 * @param map : the current in game map
 * @return true if the map is valid, false otherwise
 */
bool MAP_isMapValid(const TMap* map);

/**
 * @brief Check if the character imported from the file is valid
 * @param character : the imported character
 * @return true if the character imported from the file is valid, false otherwise
 */
bool MAP_isCharacterImportedValid(char character);

/**
 * @brief Check if the character present on the map is valid
 * @param character : the character present on the map
 * @return true if the character is a valid character to be on the map, false otherwise
 */
bool MAP_isCharacterMapValid(char character);

/**
 * @brief Check if the element at the indicated position is a food element
 * @param map : the current map
 * @param x : x coordinate of the element
 * @param y : y coordinate of the element
 * @return true if the element at (x,y) is a food element, false otherwise
 */
bool MAP_isElementFood(const TMap* map, size_t x, size_t y);

/**
 * @brief Check if the element pointed in the indicated direction from the position (x,y) is a Wall
 * @param map : the current in game map
 * @param x : x coordinate of the source point
 * @param y : y coordinate of the source point
 * @param direction : the direction to look at
 * @return true if the element pointed by the direction from (x,y) is a wall, false otherwise
 */
bool MAP_isWall(const TMap* map, size_t x, size_t y, enum EEvent direction);

/**
 * @brief Check if a particular coordinate represent a valid map coordinate
 * @param x
 * @param y
 * @return true if the element at (x,y) represent a valid coordinate, false otherwise
 */
bool MAP_isValidMapCoordinate(size_t x, size_t y);

/**
 * @brief Load the map from the file
 * @param map
 * @return true if the map was successfully loaded, false otherwise
 */
bool MAP_loadMap(TMap* map);

/**
 * @brief Remove movable element from the map in order to separate movable and unmovable element
 * @param map : the current in game map
 * @return true if the removal was successful, false otherwise
 */
bool MAP_removeMovableElement(TMap* map);

/**
 * @brief Remove food element located at (x,y) from the map
 * @param map : the current in game map
 * @param x : the x coordinate of the food element
 * @param y : the y coordinate of the food element
 * @return true if the removal was successful, false otherwise
 */
bool MAP_removeFoodElement(TMap* map, size_t x, size_t y);

/**
 * @brief Insert a movable elements into the map
 * @param map : the on which we insert the movable elements
 * @param pacman : the current pacman controlled by the player
 * @param ghosts : the ghosts controlled by the AI
 * @return true if the insertion was successful, false otherwise
 */
bool MAP_insertMovableElement(TMap* map, const TPacman pacman, const TGhost ghosts[2]);

#endif