#ifndef CARD_H
#define CARD_H

#include <cstdbool>
#include "color.h"
#include "suits.h"
#include "values.h"

class card
{
public:
    card(bool revealed, value newvalue, suit newsuit);

private:
    bool r;  // Card revealed or not
    suit s;  // Suit of card
    value v; // Value of card

// Setters
public:
    void hide(void);
    void reveal(void);

// Getters
public:
    bool getRevealed(void);
    color getColor(void);
    suit getSuit(void);
    value getValue(void);
};

#endif
