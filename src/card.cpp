#include "../include/card.h"

card::card(bool revealed, value newvalue, suit newsuit)
{
    s = newsuit;
    v = newvalue;
    r = revealed;
}

bool card::getRevealed(void) { return r; }

color card::getColor(void) { return (color) ((int) s % 2); }

suit card::getSuit(void) { return s; }

value card::getValue(void) { return v; }

void card::hide(void) { r = false; }

void card::reveal(void) { r = true; }
