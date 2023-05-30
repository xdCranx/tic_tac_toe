#ifndef BOARD.HPP
#define BOARD.HPP

#include <iostream>
#include <vector>

class Board {

private:
    std::vector<std::vector<char>> Brd;


public:

    Board();
    ~Board();

    void move();
    



};
#endif