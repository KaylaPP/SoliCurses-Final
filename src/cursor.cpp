#include "../include/cursor.h"
#include "../include/direction.h"

DynamicCursor::DynamicCursor(std::vector<size_t> maxes)
{
    for(size_t i = 0; i < maxes.size(); i++)
    {
        cursors.push_back({ 0, (int) maxes.at(i) });
    }
}

size_t DynamicCursor::getPos(void) { return cursors.at(select).pos; }

size_t DynamicCursor::getSelect(void) { return select; }

void DynamicCursor::move(direction d)
{
    int * p = &cursors.at(select).pos;
    switch(d)
    {
    case direction::up:
        select--;
        if(select < 0)
            select = cursors.size() - 1;
        break;
    case direction::down:
        select++;
        if(select >= cursors.size())
            select = 0;
    case direction::left:
        p[0]--;
        if(*p < 0)
            *p = cursors.size() - 1;
        break;
    case direction::right:
        p[0]++;
        if(*p >= cursors.size())
            *p = 0;
        break;
    };
}