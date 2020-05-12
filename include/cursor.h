#ifndef CURSOR_H
#define CURSOR_H

#include "direction.h"

// Cursors with a range of [0, xmax] or [0, ymax] [inclusive]

class cursor 
{
private:
    int y;
    int x;
    int ymax;
    int xmax;
public:
    cursor(int ym, int xm);
    int ypos(void);
    int xpos(void);
    void move(direction dir);
};

#endif
