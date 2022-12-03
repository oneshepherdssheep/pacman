#include "map.h"

bool isMapValid(TMap *map)
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
                if(!isCharacterMapValid((*map)[line][column]))
                {
                    valid = false;
                    break;
                }
            }
        }
    }
    return valid;
}

bool isCharacterImportedValid(char character)
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

bool isCharacterMapValid(char character)
{
    if(isCharacterImportedValid(character) || (character==' '))
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t getFoodCount(const TMap* map)
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
const char * getMapFilePath()
{
    return  "../Assets/map.txt";
}

TPoint getPacmanInitialPosition(TMap* map)
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
TPoint getGhostInitialPosition(TMap* map,size_t index)
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



void setInSideMapValue(TMap* map, char value, u_int8_t x, u_int8_t y)
{
    if((isCharacterImportedValid(value)) && (y + 1 < MAP_LINE_COUNT) && (x + 3 < MAP_COLUMN_COUNT))
    {
        (*map)[y+1][x+3] = value;
    }
}

void initMap(TMap* map)
{
    for(u_int8_t line = 0; line < MAP_LINE_COUNT; line++)
    {
        for(u_int8_t column=0; column < MAP_COLUMN_COUNT; column++)
        {
            // empty by default
            (*map)[line][column] = ' ';

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

MapOperationResult loadMap(TMap* map)
{
    FILE *filePointer;

    // Set outer walls
    initMap(map);

    printf("\n");

    char buffer[MAP_FILE_COLUMN_COUNT];
    // open the Assets/file map_g.txt
    filePointer = fopen(getMapFilePath(),"r");

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
                if(isCharacterImportedValid(buffer[i]))
                {
                    setInSideMapValue(map,buffer[i],columnCounter,lineCounter);
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
    fclose(filePointer);

    return MAP_OK;
}

void printMap(TMap* map)
{
    printf("\n");
    printf("%s",(*map)[0]);
}

void insertMoveableElement(TMap* map,const TPacman pacman,const TGhost ghosts[2])
{
    (*map)[pacman.position.y][pacman.position.x] = PACMAN;
    (*map)[ghosts[0].position.y][ghosts[0].position.x] = GHOST;
    (*map)[ghosts[1].position.y][ghosts[1].position.x] = GHOST;
}


void removeMoveableElement(TMap* map)
{
    for(size_t line = 0; (line < MAP_LINE_COUNT); line++)
    {
        for(size_t column=0; (column < MAP_COLUMN_COUNT); column++)
        {
            if((*map)[line][column]==PACMAN || (*map)[line][column]==GHOST)
            {
                (*map)[line][column] = ' ';
            }
        }
    }
}

bool isElementFood(TMap* map,size_t x,size_t y)
{
    if(isCoordinatesValid(x,y))
    {
        return (*map)[y][x]==DOT;
    }
    else
    {
        return false;
    }
}

void removeFoodElement(TMap* map,size_t x,size_t y)
{
    if(isElementFood(map,x,y))
    {
        (*map)[y][x]=' ';
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

bool isCoordinatesValid(size_t x, size_t y)
{
    return (x < MAP_COLUMN_COUNT) && (y < MAP_LINE_COUNT);
}

bool isWall(TMap* map, size_t x, size_t y, enum TEvent direction)
{
    if(isCoordinatesValid(x,y) && isDirectionEvent(direction))
    {
        // UP
        if(direction==MOVE_UP && isCoordinatesValid(x,y-UP_DOWN_STEP))
        {
            return (*map)[y-UP_DOWN_STEP][x]==WALL;
        }
        // DOWN
        else if(direction==MOVE_DOWN && isCoordinatesValid(x,y+UP_DOWN_STEP))
        {
            return (*map)[y+UP_DOWN_STEP][x]==WALL;
        }
        // RIGHT
        else if(direction==MOVE_RIGHT && isCoordinatesValid(x+LEFT_RIGHT_STEP,y))
        {
            return (*map)[y][x+LEFT_RIGHT_STEP]==WALL;
        }
        // LEFT
        else if(direction==MOVE_LEFT && isCoordinatesValid(x-LEFT_RIGHT_STEP,y))
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



