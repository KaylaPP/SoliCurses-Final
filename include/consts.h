#ifndef CONSTS_H
#define CONSTS_H

static const char val_ch[4] = "JQK";
static const int card_width = 5;
static const int card_height = 4;

// Strings that represent different UTF-8 characters for card suits
static const char suit_ch[4][4] =
{
    "\xE2\x99\xA0", // Spade
    "\xE2\x99\xA6", // Diamond
    "\xE2\x99\xA3", // Club
    "\xE2\x99\xA5"  // Heart
};

#endif
