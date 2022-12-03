#include "map.h"

bool MAP_isMapValid(const TMap *map)
{
    bool valid = true;
    for(size_t line = 0; line < MAP_LINE_COUNT; line++)
    {
        for(size_t column=0; column < MAP_COLUMN_COUNT; column++)
        {
            // outer wall
            if(
                ((line==0) && (column%3==0)) ||
                ((line==(MAP_LINE_COUNT - 1)) && (column%3==0)) ||
                (column == 0) ||
                (column == (MAP_COLUMN_COUNT - 2))
              )
            {
                if((*map)[line][column] != WALL)
                {
                    valid = false;
                    break;
                }
            }
            else if(column == (MAP_COLUMN_COUNT-1))
            {
                if((*map)[line][column] != '\n')
                {
                    valid = false;
                    break;
                }
            }
            // other element inside
            else
            {
                if(!MAP_isCharacterMapValid((*map)[line][column]))
                {
                    valid = false;
                    break;
                }
            }
        }
    }
    return valid;
}

bool MAP_isCharacterImportedValid(char character)
{
    if((character==PACMAN) || (character==GHOST) || (character==WALL) || (character==DOT))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MAP_isCharacterMapValid(char character)
{
    if(MAP_isCharacterImportedValid(character) || (character == EMPTY))
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t MAP_getFoodCount(const TMap* map)
{
    size_t foodCount = 0;
    for(size_t line = 0; line < MAP_LINE_COUNT; line++)
    {
        for(size_t column=0; column < MAP_COLUMN_COUNT; column++)
        {
            if((*map)[line][column]==DOT)
            {
                foodCount++;
            }
        }
    }
    return foodCount;
}

//
const char * MAP_getMapFilePath()
{
    return  "../Assets/map.txt";
}

TPoint MAP_getPacmanInitialPosition(TMap* map)
{
    TPoint pacmanInitialPoint = {0,0};
    bool found = false;
    for(size_t line = 0; (line < MAP_LINE_COUNT) && !found; line++)
    {
        for(size_t column=0; (column < MAP_COLUMN_COUNT) && !found; column++)
        {
            if((*map)[line][column]==PACMAN)
            {
                pacmanInitialPoint.x = (int)column;
                pacmanInitialPoint.y = (int)line;
                found = true;
            }
        }
    }
    return pacmanInitialPoint;
}

// first ghost : index = 0
// second ghost : index = 1
TPoint MAP_getGhostInitialPosition(TMap* map, size_t index)
{
    TPoint ghostInitialPoint = {0,0};
    bool found = false;
    size_t ghostIndex = 0;
    for(size_t line = 0; (line < MAP_LINE_COUNT) && !found; line++)
    {
        for(size_t column=0; (column < MAP_COLUMN_COUNT) && !found; column++)
        {
            if((*map)[line][column]==GHOST)
            {
                if(index==ghostIndex)
                {
                    ghostInitialPoint.x = (int)column;
                    ghostInitialPoint.y = (int)line;
                    found = true;
                }
                ghostIndex++;
            }
        }
    }
    return ghostInitialPoint;
}



void MAP_setInSideMapValue(TMap* map, char newValue, u_int8_t newValue_x, u_int8_t newValue_y)
{
    if((MAP_isCharacterImportedValid(newValue)) && (newValue_y + 1 < MAP_LINE_COUNT) && (newValue_x + 3 < MAP_COLUMN_COUNT))
    {
        (*map)[newValue_y + 1][newValue_x + 3] = newValue;
    }
}

void MAP_initMap(TMap* map)
{
    for(u_int8_t line = 0; line < MAP_LINE_COUNT; line++)
    {
        for(u_int8_t column=0; column < MAP_COLUMN_COUNT; column++)
        {
            // empty by default
            (*map)[line][column] = EMPTY;

            // outer wall
            if(
                (((line==0) && (column%3==0)) ||
                ((line==(MAP_LINE_COUNT - 1)) && (column%3==0)) ||
                (column == 0) ||
                (column == (MAP_COLUMN_COUNT - 2)))
                )
            {
                (*map)[line][column] = WALL;
            }

            // new line character
            if(column==(MAP_COLUMN_COUNT - 1))
            {
                (*map)[line][column] = '\n';
            }
        }
    }
}

bool MAP_loadMap(TMap* map)
{
    bool mapLoaded = true;
    FILE *filePointer;

    // Set outer walls
    MAP_initMap(map);

    printf("\n");

    char buffer[MAP_FILE_COLUMN_COUNT];
    // open the Assets/file map_g.txt
    filePointer = fopen(MAP_getMapFilePath(), "r");

    // set the beginning of the file
    if(filePointer!=NULL)
    {
        fseek(filePointer,0,SEEK_SET);

        // read the file
        u_int8_t lineCounter = 0;
        u_int8_t columnCounter = 0;

        while(fread(buffer,sizeof(*buffer),sizeof(buffer)/sizeof(buffer[0]),filePointer))
        {
            for(u_int8_t i = 0; i < MAP_FILE_COLUMN_COUNT; i++)
            {
                if(MAP_isCharacterImportedValid(buffer[i]))
                {
                    MAP_setInSideMapValue(map, buffer[i], columnCounter, lineCounter);
                    columnCounter+=3;
                    if(columnCounter>=MAP_FILE_COLUMN_COUNT)
                    {
                        lineCounter++;
                        columnCounter=0;
                    }
                    if(lineCounter>=MAP_FILE_LINE_COUNT)
                    {
                        break;
                    }
                }
            }
        }
    }
    else
    {
        mapLoaded = false;
    }
    fclose(filePointer);

    return mapLoaded;
}

void printMap(TMap* map)
{
    printf("\n");
    printf("%s",(*map)[0]);
}

void MAP_insertMovableElement(TMap* map, const TPacman pacman, const TGhost ghosts[2])
{
    (*map)[pacman.position.y][pacman.position.x] = PACMAN;
    (*map)[ghosts[0].position.y][ghosts[0].position.x] = GHOST;
    (*map)[ghosts[1].position.y][ghosts[1].position.x] = GHOST;
}


void MAP_removeMovableElement(TMap* map)
{
    for(size_t line = 0; (line < MAP_LINE_COUNT); line++)
    {
        for(size_t column=0; (column < MAP_COLUMN_COUNT); column++)
        {
            if((*map)[line][column]==PACMAN || (*map)[line][column]==GHOST)
            {
                (*map)[line][column] = EMPTY;
            }
        }
    }
}

bool MAP_isElementFood(const TMap* map, size_t x, size_t y)
{
    if(MAP_isCoordinatesValid(x, y))
    {
        return (*map)[y][x]==DOT;
    }
    else
    {
        return false;
    }
}

void MAP_removeFoodElement(TMap* map, size_t x, size_t y)
{
    if(MAP_isElementFood(map, x, y))
    {
        (*map)[y][x]=EMPTY;
    }
    else
    {
        // nothing to do
    }
}

bool isCoordinatesValidForAMove(size_t x, size_t y)
{
    return (x >= LEFT_RIGHT_STEP) && (x < MAP_COLUMN_COUNT) && (y >= UP_DOWN_STEP) && (y < MAP_LINE_COUNT);
}

bool MAP_isCoordinatesValid(size_t x, size_t y)
{
    return (x < MAP_COLUMN_COUNT) && (y < MAP_LINE_COUNT);
}

bool MAP_isWall(const TMap* map, size_t x, size_t y, enum TEvent direction)
{
    if(MAP_isCoordinatesValid(x, y) && UTILS_isDirectionEvent(direction))
    {
        // UP
        if(direction==MOVE_UP && MAP_isCoordinatesValid(x, y - UP_DOWN_STEP))
        {
            return (*map)[y-UP_DOWN_STEP][x]==WALL;
        }
        // DOWN
        else if(direction==MOVE_DOWN && MAP_isCoordinatesValid(x, y + UP_DOWN_STEP))
        {
            return (*map)[y+UP_DOWN_STEP][x]==WALL;
        }
        // RIGHT
        else if(direction==MOVE_RIGHT && MAP_isCoordinatesValid(x + LEFT_RIGHT_STEP, y))
        {
            return (*map)[y][x+LEFT_RIGHT_STEP]==WALL;
        }
        // LEFT
        else if(direction==MOVE_LEFT && MAP_isCoordinatesValid(x - LEFT_RIGHT_STEP, y))
        {
            return (*map)[y][x-LEFT_RIGHT_STEP]==WALL;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}



