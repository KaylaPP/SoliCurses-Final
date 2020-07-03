#ifndef CURSOR_H
#define CURSOR_H

#include <vector>
#include "direction.h"

struct cursor
{
    int pos;
    int max;
};

class DynamicCursor
{
public:
    DynamicCursor(std::vector<size_t> maxes);
    int getPos(void);
    int getSelect(void);
    void move(direction d);

private:
    std::vector<cursor> cursors;
    int select;
};

#endif
