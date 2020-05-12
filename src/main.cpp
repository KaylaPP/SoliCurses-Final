#include <clocale>
#include <cstdbool>
#include <cstdlib>
#include <ctime>
#include <curses.h>
#include <iostream>
#include "../include/piles.h"
#include "../include/card.h"
#include "../include/consts.h"
#include "../include/cursor.h"
#include "../include/gb.h"
#include "../include/suits.h"
#include "../include/values.h"

int main(void)
{
    setlocale(LC_ALL, "en_US.UTF-8");

    int input = 0;
    GameBoard * board = new GameBoard();

    do 
    {
        input = getch();
        board->input(input);
    } while(input == ERR);

    bool win = board->getWon();
    int score = board->getScore();
    time_t elapsed = board->getElapsed();
    delete board;

    if(win)
        std::cout << "Congratulations!" << std::endl;
    std::cout << "Your score was " << score << " and your elapsed time was " << elapsed << " seconds." << std::endl;

    return 0;
}
