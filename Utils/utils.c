#include "utils.h"
#include "../Map/map.h"

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



bool UTILS_isPointCloseToPoint(TPoint p1, TPoint p2)
{
    // UP
    if((p1.x==p2.x) && ((p1.y-UP_DOWN_STEP)==p2.y))
    {
        return true;
    }
        // DOWN
    else if((p1.x==p2.x) && ((p1.y+UP_DOWN_STEP)==p2.y))
    {
        return true;
    }
        // RIGHT
    else if((p1.x+LEFT_RIGHT_STEP==p2.x) && ((p1.y)==p2.y))
    {
        return true;
    }
        // LEFT
    else if((p1.x-LEFT_RIGHT_STEP==p2.x) && ((p1.y)==p2.y))
    {
        return true;
    }
    else
    {
        return false;
    }
}