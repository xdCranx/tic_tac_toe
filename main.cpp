#include <iostream>
#include "Board.hpp"

const int SIZE = 3;
const int BOT_DEPTH = 3;


int main(int argc, char *argv[]) {

    Board game(SIZE);
    do {
        
        std::cout << "Bot moved" << std::endl;
        game.move(game.minmax(BOT_DEPTH, 'O'), 'O');
        game.printBoard();
        if(game.isGameOver()) break;
        game.inputMove();
        system("cls");
        
        
    } while (true);



    return 0;
}