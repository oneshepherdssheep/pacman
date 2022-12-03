#include "utils.h"

bool UTILS_isDirectionEvent(enum EEvent event)
{
    if(
        (event==MOVE_RIGHT) ||
        (event==MOVE_LEFT) ||
        (event==MOVE_DOWN) ||
        (event==MOVE_UP)
       )
    {
        return true;
    }
    else
    {
        return false;
    }

}