#ifndef CURSOR_H
#define CURSOR_H

#include <vector>
#include "direction.h"

class DynamicCursor
{
public:
    DynamicCursor(std::vector<size_t> maxes);
    void move(direction d);

private:
    struct cursor 
    {
        size_t pos;
        size_t max;
    };
    std::vector<cursor> cursors;
    size_t select;

};

#endif
