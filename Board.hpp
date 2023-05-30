#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

class Board {

private:
    const char EMPTY_CELL = ' ';    
    const char PLAYER_X = 'X';
    const char PLAYER_O = 'O';

    std::vector<std::vector<char>> BOARD;

    int boardSize;


public:
    // Checks single row
    bool checkROW(const int ROW) {
        for(int COL = 0; COL < boardSize; COL++) {
            if (BOARD[ROW][COL] != BOARD[ROW][COL+1] )
                return false;
            else continue;
        }
        return true;
    };
    
    // Checks single col
        bool checkCOL(const int COL) {
        for(int ROW = 0; ROW < boardSize; ROW++) {
            if (BOARD[ROW][COL] != BOARD[ROW+1][COL] )
                return false;
            else continue;
        }
        return true;
    };
    
    // Checks win
    bool checkWin(char player) {

        // Checks all rows
        for (int ROW = 0; ROW < boardSize; ROW++) {
            if (checkROW(ROW)) {
                return true;
            }
            else continue;
        }
        // Checks all cols
        for (int COL = 0; COL < boardSize; COL++) {
            if (checkCOL(COL)) {
                return true;
            }
            else continue;
        };
        // Checks diagonals
        for (int ROW = 0; ROW < boardSize; ROW++)
            for(int COL = 0; COL < boardSize; COL--)
                if(BOARD[ROW][COL] == BOARD[ROW++][COL++])
                    



    };








};  
#endif