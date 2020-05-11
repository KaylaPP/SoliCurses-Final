#include <curses.h>
#include <clocale>
#include <cstdbool>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../include/board.h"
#include "../include/card.h"
#include "../include/consts.h"
#include "../include/cursor.h"
#include "../include/gb.h"
#include "../include/suits.h"
#include "../include/values.h"

int main(int argv, char * argc[])
{
    int input = 0;
    GameBoard * board = new GameBoard();

    board->print();
    do 
    {
        input = getch();
    } while(input == ERR);

    delete board;

    return 0;
}
