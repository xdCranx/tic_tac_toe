#include <iostream>
#include "Board.hpp"

const int SIZE = 3;
const int BOT_DEPTH = 6;

int main(int argc, char *argv[])
{

    Board game(SIZE);
    do
    {
        system("cls");
        game.move(game.minmax(BOT_DEPTH, 'O'), 'O');
        std::cout << "Bot moved\n" << std::endl;
        game.printBoard();
        if (game.isGameOver())
            break;
        game.inputMove();
        system("cls");

    } while (true);

    return 0;
}