#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <iostream>

const int MAX = 10000;
const int MIN = -10000;

typedef std::vector<std::vector<char>> brd_type;

class Board {

private:
    const char EMPTY_CELL = ' ';    
    const char PLAYER = 'X';
    const char BOT = 'O';
    std::vector<std::vector<std::vector<int>>> WIN_POS;
    int BOARD_SIZE;
    brd_type BOARD;


    void winBoardGen() {
        // Generate winning rows
        for (int ROW = 0; ROW < BOARD_SIZE; ROW++) {
            std::vector<std::vector<int>> pos;
            for(int COL = 0; COL < BOARD_SIZE; COL++) {
            std::vector<int> index(2);
            index[0] = ROW;
            index[1] = COL;
            pos.push_back(index);
            };
            WIN_POS.push_back(pos);   
        };

        // Generate winning columns
        for (int ROW = 0; ROW < BOARD_SIZE; ROW++) {
            std::vector<std::vector<int>> pos;
            for(int COL = 0; COL < BOARD_SIZE; COL++) {
                std::vector<int> index(2);
                index[0] = COL;
                index[1] = ROW;
                pos.push_back(index);
            };
            WIN_POS.push_back(pos);   
        };

        // Generate 1-st diagonal
        std::vector<std::vector<int>> d1pos;
        for(int i = 0 ; i < BOARD_SIZE; i++) {
            std::vector<int> index(2);
            index[0] = index[1] = i;
            d1pos.push_back(index);
        };
        WIN_POS.push_back(d1pos);

        // Generate 2-nd diagonal
        std::vector<std::vector<int>> d2pos;
        for(int i = 0 ; i < BOARD_SIZE; i++) {
            std::vector<int> index(2);
            index[0] = (BOARD_SIZE - 1) - i;
            index[1] = i;
            d2pos.push_back(index);
        };
        WIN_POS.push_back(d2pos);


};





public:

    Board(int size) {
        BOARD_SIZE = size;
        BOARD = setBoard(size);
        winBoardGen();
    };

    ~Board() {};

    std::vector<std::vector<char>> setBoard(int size) {

        std::vector<std::vector<char>> BOARD(size, std::vector<char>(size, ' '));
        return BOARD;
    };
    
    bool isBoardFull() {
        
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (BOARD[i][j] == EMPTY_CELL)
                    return false;
            }
            return true;
        }
    };

    //Add evaluating in bot's prediction
    int evaluate() {

    //Iterate through all possible wins to check win
        for (int i = 0; i < 2*BOARD_SIZE+2; i++)
        {
        //Check for player's win
            int isMAX = 0;
            for(int j = 0; j < BOARD_SIZE; j++) {
                if ((BOARD[WIN_POS[i][j][0]][WIN_POS[i][j][1]] != PLAYER))
                {
                    break;
                }
                else isMAX++;
            }
            if(isMAX==BOARD_SIZE) return 10000;
        
        //Check for bot's win
            int isMIN = 0;
            for(int j =0; j < BOARD_SIZE; j++) {
                if ((BOARD[WIN_POS[i][j][0]][WIN_POS[i][j][1]] != BOT))
                {
                    break;
                }
                isMIN++;
            }
            if(isMIN==BOARD_SIZE) return -10000;
        }
    
    //Iterate through all possible wins to evaluate
        int eval = 0;
        for (int i = 0; i < 2*BOARD_SIZE+2; i++)
        {
            int isMAX = 0;
            for(int j = 0; j < BOARD_SIZE; j++) {
                if ((BOARD[WIN_POS[i][j][0]][WIN_POS[i][j][1]] != BOT))
                {
                    isMAX++;
                }
            }
            if(isMAX==BOARD_SIZE) eval++;
            
            int isMIN = 0;
            for(int j =0; j < BOARD_SIZE; j++) {
                if ((BOARD[WIN_POS[i][j][0]][WIN_POS[i][j][1]] != PLAYER))
                {
                    isMIN++;
                }
            }
            if(isMIN==BOARD_SIZE) eval--;
        }
        return eval;
    };

   
    void printWinPos()
    {
        // Iterate over the elements of the vector
        for (const auto& dim1 : WIN_POS) {
            for (const auto& dim2 : dim1) {
                for (const auto& element : dim2) {
                    std::cout << element << " ";
                }
                std::cout << std::endl;  // Print a newline after each 2D matrix
            }
            std::cout << std::endl;  // Print an additional newline after each 3D layer
        }
    }

    void printBoard() {
        for(int rows = 0; rows < BOARD_SIZE; rows++) {
            for(int cols = 0; cols < BOARD_SIZE; cols++) {
                std::cout << BOARD[rows][cols];
                if(cols < BOARD_SIZE-1) std::cout << " | ";
            }
            std::cout << std::endl;
            for(int n = 0; n < 3*(BOARD_SIZE-1)+BOARD_SIZE; n++) if(rows<BOARD_SIZE-1) std::cout<<"-";
            std::cout << std::endl;
        }
}


    int minmaxrec(brd_type state, int depth, int a, int b, bool isMAX)
{
    int value = evaluate();
    if (depth == 0 || value == MIN || value == MAX)
        return value;

    bool prune = false;

    if (isMAX)
    {
        int maxEval = MIN;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (state[i][j] == 0)
                {
                    brd_type nextState = state;
                    nextState[i][j] = 1;

                    int eval = minmaxrec(nextState, depth - 1, a, b, false);
                    maxEval = std::max(maxEval, eval);
                    a = std::max(a, eval);

                    if (b <= a)
                    {
                        prune = true;
                        break;
                    }
                }
            }
            if (prune) { break; }
        }
        return maxEval;
    }
    else
    {
        int minEval = MAX;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (state[i][j] == 0)
                {
                    brd_type nextState = state;
                    nextState[i][j] = 2;

                    int eval = minmaxrec(nextState, depth - 1, a, b, true);
                    minEval = std::min(minEval, eval);
                    b = std::min(b, eval);

                    if (b <= a)
                    {
                        prune = true;
                        break;
                    }
                }
            }
            if (prune) { break;}
        }
        return minEval;
    }
}

};  
#endif