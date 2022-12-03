#include "input.h"
#include "colours.h"

bool INPUT_isEventAMove(enum TEvent event)
{
    if(event==MOVE_UP || event==MOVE_DOWN || event==MOVE_LEFT || event==MOVE_RIGHT)
    {
        return true;
    }
    else
    {
        return false;
    }
}

enum TEvent INPUT_getLastUserInputEvent()
{
    char typedCharacter = getch();//getchar();
    if(typedCharacter == UP)
    {
        return MOVE_UP;
    }
    else if(typedCharacter == DOWN)
    {
        return MOVE_DOWN;
    }
    else if(typedCharacter == LEFT)
    {
        return MOVE_LEFT;
    }
    else if(typedCharacter == RIGHT)
    {
        return MOVE_RIGHT;
    }
    else if(typedCharacter == QUIT)
    {
        return EXIT;
    }
    else
    {
        return NONE;
    }
}


