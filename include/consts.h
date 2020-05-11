#pragma once

static const char val_ch[4] = "JQK";
static const int card_width = 4;
static const int card_height = 3;

#ifndef _MSVC_TRADITIONAL
// Strings that represent different UTF-8 characters for card suits
static const char suit_ch[4][4] =
{
    "\xE2\x99\xA0", // Spade
    "\xE2\x99\xA6", // Diamond
    "\xE2\x99\xA3", // Club
    "\xE2\x99\xA5"  // Heart
};

#else

#include <wchar.h>
// Strings that represent different UTF-16 characters for card suits
static const wchar_t suit_ch[4][2] =
{
    L"♠", // Spade
    L"♦", // Diamond
    L"♣", // Club
    L"♥"  // Heart
};

#endif
