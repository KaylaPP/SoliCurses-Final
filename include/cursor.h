#ifndef CURSOR_H
#define CURSOR_H

#include <vector>
#include "direction.h"

class DynamicCursor
{
public:
    DynamicCursor(std::vector<int> maxes);
    void move(direction d);

private:
    struct cursor 
    {
        int pos;
        int max;
    };
    std::vector<cursor> cursors;
    int select;

};

#endif
