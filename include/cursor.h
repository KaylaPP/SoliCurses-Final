#ifndef CURSOR_H
#define CURSOR_H

#include <vector>
#include "direction.h"

class DynamicCursor
{
public:
    DynamicCursor(std::vector<size_t> maxes);
    size_t getPos(void);
    size_t getSelect(void);
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
