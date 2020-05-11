#include "../include/cursor.h"
#include "../include/direction.h"

cursor::cursor(int ym, int xm)
{
    y = 0;
    x = 0;
    ymax = ym;
    xmax = xm;
}

int cursor::ypos(void) { return y; }

int cursor::xpos(void) { return x; }

void cursor::move(direction dir)
{
    switch(dir)
    {
    default:
        break;
    case up:
        y--;
        if(y < 0)
            y = 0;
        break;
    case down:
        y++;
        if(y > ymax)
            y = ymax;
        break;
    case left:
        x--;
        if(x < 0)
            x = 0;
        break;
    case right:
        x++;
        if(x > xmax)
            x = xmax;
        break;
    }
}
