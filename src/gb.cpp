#include <curses.h>
#include <stdexcept>
#include "../include/consts.h"
#include "../include/gb.h"

// Cyan is being redefined to gray in startcurses() so this macro is made to preserve readability
#define COLOR_GRAY COLOR_CYAN

// Activates all attributes for the terminal using curses
static void startcurses(void);

GameBoard::GameBoard(void)
{
    startcurses();
    c = new cursor(0, 0);
    gb = new std::vector<card *>[12];
    hiddencard = new card(false, Ace, Spade);

    // Initialize all cards in deck with default values
    uint32_t count = 0;
    for(uint32_t s = Spade; s <= Heart; s++)
    {
        for(uint32_t v = Ace; v <= King; v++)
        {
            deck[count++] = new card(false, (value) v, (suit) s);
        }
    }
    
    // Shuffle cards in deck
    srand(time(nullptr));
    for(count = 0; count < 52; count++)
    {
        int r1 = rand() % 52;
        int r2 = rand() % 52;

        card * rcard = deck[r1];

        deck[r1] = deck[r2];
        deck[r2] = rcard;
    }

    // Add cards to board (gb)
    count = 0;
    for(uint32_t i = T1; i <= T7; i++)
    {
        for(uint32_t j = 0; j <= i - T1; j++)
            gb[i].push_back(deck[count++]);

        if(gb[i].size() > 0)
            gb[i].back()->reveal();
    }

    while(count < 52)
    {
        gb[DS].push_back(deck[count++]);
    }

    starttime = time(nullptr);
    gamestart = true;
    gamestop = false;
    gamewin = false;

}

GameBoard::~GameBoard(void)
{
    /*
    TODO: Implement this function to free all pointers in GameBoard
    */
    endwin();
}

time_t GameBoard::elapsed(void)
{
    return time(nullptr) - starttime;
}

void GameBoard::input(int inp)
{
    attron(COLOR_PAIR(3));
    mvprintw(0, 0, "Time elapsed: %i", elapsed());
    attron(COLOR_PAIR(1));


    switch(inp)
    {
    default:
        break;

    // Exit prompt
    case 'e':
    case 'E':
        break;

    // Draw card
    case 'd':
    case 'D':
        break;

    // Select card for movement then select location for movement
    case ' ':
        break;

    case KEY_UP:
        break;

    case KEY_DOWN:
        break;

    case KEY_RIGHT:
        break;

    case KEY_LEFT:
        break;
    }
}

void GameBoard::print()
{
    printBackground();
    printDeck(2, 4);

    // Print Foundation
    for(int i = F1; i <= F4; i++)
    {
        printCard(2, 24 + 10 * i, lastRevealed((pile) i));
    }

    // Print Tableau
    for(uint32_t i = T1; i <= T7; i++)
    {
        for(uint32_t j = 0; j < gb[i].size(); j++)
        {
            printCard(8 + 2 * j, 10 * i - 46, gb[i].at(j));
        }
    }
}

void GameBoard::refresh()
{
    // Flip last cards in tableau face up
    for(uint32_t y = T1; y <= T7; y++)
    {
        if(gb[y].size() > 0)
            gb[y].back()->reveal();
    }

    // Leaves all cards in foundation except the last flipped face up
    for(uint32_t y = F1; y <= F4; y++)
    {
        if(gb[y].size() > 0)
        {    
            for(uint32_t x = 0; x < gb[y].size(); x++)
            {
                gb[y].at(x)->reveal();
            }
            gb[y].back()->reveal();
        }
    }
}

card * GameBoard::lastRevealed(pile p)
{
    if(gb[p].size() > 0)
        return gb[p].back();
    return nullptr;
}

uint32_t GameBoard::totalRevealed(pile p)
{
    uint32_t total = 0;
    for(uint32_t i = 0; i < gb[p].size(); i++)
    {
        if(gb[p].at(i)->getRevealed())
            total++;
    }
    return total;
}

void GameBoard::printBackground(void)
{
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1));
    for(int y = 0; y < 100; y++)
    {
        for(int x = 0; x < 1000; x++)
        {
            mvprintw(y, x, " ");
        }
    }
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1));
}

void GameBoard::printCard(int y, int x, card * c)
{
    if(c == nullptr)
    {
        printEmptyCard(y, x);
        return;
    }

#ifndef RANDOMSTRINGOFLETTERS
    if(!c->getRevealed()) // If card is not revealed
    {
        printHiddenCard(y, x);
        return;
    }
#endif
    int color;
    if(c->getColor() == black)
        color = 3;
    else /* if color is red */
        color = 2;

    // Apply color attributes
    attron(COLOR_PAIR(color));

    // Print white card background
    for(int yc = y; yc < y + card_height; yc++)
    {
        for(int xc = x; xc < x + card_width; xc++)
        {
            mvprintw(yc, xc, " ");
        }
    }

    attron(COLOR_PAIR(color + 5));

    // Print card suit symbol
    mvprintw(y, x, "%s", suit_ch[c->getSuit()]);
    mvprintw(y + card_height - 1, x + card_width - 1, "%s", suit_ch[c->getSuit()]);

    // Print card value
    if(c->getValue() == Ace)
    {
        mvprintw(y, x + card_width - 1, "A");
        mvprintw(y + card_height - 1, x, "A");
    }
    else if(c->getValue() >= Two && c->getValue() < Ten)
    {
        mvprintw(y, x + card_width - 1, "%i", c->getValue() + 1);
        mvprintw(y + card_height - 1, x, "%i", c->getValue() + 1);
    }
    else if(c->getValue() == Ten)
    {
        mvprintw(y, x + card_width - 2, "10");
        mvprintw(y + card_height - 1, x, "10");
    }
    else if(c->getValue() >= Jack)
    {
        mvprintw(y, x + card_width - 1, "%c", val_ch[c->getValue() - Jack]);
        mvprintw(y + card_height - 1, x, "%c", val_ch[c->getValue() - Jack]);
    }

    // Remove color attributes
    attron(COLOR_PAIR(1));
}

void GameBoard::printDeck(int y, int x)
{
    if(totalRevealed(DS) == 0)
        printHiddenCard(y, x);
    else
        printEmptyCard(y, x);
}

void GameBoard::printEmptyCard(int y, int x)
{
    attron(COLOR_PAIR(7));
    for(int yc = y; yc < y + card_height; yc++)
    {
        for(int xc = x; xc < x + card_width; xc++)
        {
            mvprintw(yc, xc, " ");
        }
    }
    attron(COLOR_PAIR(1));
    for(int yc = y + 1; yc < y + card_height - 1; yc++)
    {
        for(int xc = x + 1; xc < x + card_width - 1; xc++)
        {
            mvprintw(yc, xc, " ");
        }
    }
}

void GameBoard::printHiddenCard(int y, int x)
{
    attron(COLOR_PAIR(3));
    for(int yc = y; yc < y + card_height; yc++)
    {
        for(int xc = x; xc < x + card_width; xc++)
        {
            mvprintw(yc, xc, " ");
        }
    }
    attron(COLOR_PAIR(4));
    for(int yc = y + 1; yc < y + card_height - 1; yc++)
    {
        for(int xc = x + 1; xc < x + card_width - 1; xc++)
        {
            mvprintw(yc, xc, " ");
        }
    }
    attron(COLOR_PAIR(1));
}


static void startcurses(void)
{
    // Initialize curses terminal attributes
    initscr();
    if(has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal doesn't support color!");
        exit(1);
    }
    start_color();

    // Check if colors can change
    if(can_change_color() == FALSE)
    {
        printw("Your terminal doesn't support changing of color attributes!\nIf you continue, the game may look weird. Is this fine? (y/N) ");
        refresh();
        int isfine;
        scanw("%c", &isfine);
        if(isfine != 'y' && isfine != 'Y')
        {
            endwin();
            exit(1);
        }
    }

    init_color(COLOR_GRAY, 600, 600, 600);

    // Initializes color pairs
    init_pair(1, COLOR_GREEN, COLOR_GREEN); // Default green background
    init_pair(2, COLOR_RED, COLOR_WHITE);   // Red text on white background
    init_pair(3, COLOR_BLACK, COLOR_WHITE);  // Black text on white background
    init_pair(4, COLOR_BLUE, COLOR_BLUE); // Blue background for hidden cards
    init_pair(5, COLOR_RED, COLOR_YELLOW);   // Red text on yellow background
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);  // Black text on yellow background
    init_pair(7, COLOR_RED, COLOR_GRAY);   // Red text on gray/cyan background
    init_pair(8, COLOR_BLACK, COLOR_GRAY);  // Black text on gray/cyan background


    // Apply default color mode and apply ncurses window attributes
    attron(COLOR_PAIR(1));
    raw();
    keypad(stdscr, true);
    noecho();
    halfdelay(1);
}
