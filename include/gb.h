#pragma once

#include <cstdbool>
#include <ctime>
#include <vector>
#include "board.h"
#include "card.h"
#include "color.h"
#include "cursor.h"

class GameBoard
{
public:
    GameBoard(void);
    ~GameBoard(void);

private:
    bool gamestart;
    bool gamestop;
    bool gamewin;
    card * deck[52];
    card * hiddencard;
    cursor * c;
    time_t starttime;
    std::vector<card *> * gb;

public:
    void input(int inp);
    void print(void);
    void refresh(void);
    time_t elapsed(void);

private:
    bool canmove(pile p1, pile p2, int ind1, int ind2);
    card * lastRevealed(pile p);
    uint32_t totalRevealed(pile p);
    void printBackground(void);
    void printCard(int y, int x, card * c);
    void printDeck(int y, int x);
    void printEmptyCard(int y, int x);
    void printHiddenCard(int y, int x);

};

/*
typedef struct
{
    Array * gb;
    bool gamestart;
    bool gamestop;
    bool gamewin;
    time_t starttime;
    time_t endttime;
} GB;

// Initializes GB with 52 cards distributed on the gameboard
void initGB(GB * gb, card * deck);

void doinput(GB * gb, Cursor * c, int input);

void printGB(GB * gb, Cursor * c);

void refreshGB(GB * gb);
*/