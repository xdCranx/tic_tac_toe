#include <iostream>
#include <vector>

using namespace std;

int boardSize = 5;
vector<vector<vector<int>>> WinPos;

// Winpos[] - single winning pos
// Winpos[][] - X && Y of player
// Winpos[][][0]/[][][1] - X/Y of player


// Winpos[2*boardSize+2][boardSize][2]
void WinPosGen() {
    // Generate einning rows
    for (int ROW = 0; ROW < boardSize; ROW++) {
        vector<vector<int>> pos;
        for(int COL = 0; COL < boardSize; COL++) {
           vector<int> index(2);
           index[0] = ROW;
           index[1] = COL;
           pos.push_back(index);
        };
        WinPos.push_back(pos);   
    };

    // Generate winning columns
    for (int ROW = 0; ROW < boardSize; ROW++) {
        vector<vector<int>> pos;
        for(int COL = 0; COL < boardSize; COL++) {
            vector<int> index(2);
            index[0] = COL;
            index[1] = ROW;
            pos.push_back(index);
        };
        WinPos.push_back(pos);   
    };

    // Generate 1-st diagonal
    vector<vector<int>> d1pos;
    for(int i = 0 ; i < boardSize; i++) {
        vector<int> index(2);
        index[0] = index[1] = i;
        d1pos.push_back(index);
    };
    WinPos.push_back(d1pos);

    // Generate 2-nd diagonal
    vector<vector<int>> d2pos;
    for(int i = 0 ; i < boardSize; i++) {
        vector<int> index(2);
        index[0] = (boardSize - 1) - i;
        index[1] = i;
        d2pos.push_back(index);
    };
    WinPos.push_back(d2pos);


};
void print3DVector(const std::vector<std::vector<std::vector<int>>>& vec)
{
    // Iterate over the elements of the vector
    for (const auto& dim1 : vec) {
        for (const auto& dim2 : dim1) {
            for (const auto& element : dim2) {
                std::cout << element << " ";
            }
            std::cout << std::endl;  // Print a newline after each 2D matrix
        }
        std::cout << std::endl;  // Print an additional newline after each 3D layer
    }
}

int main() {

    WinPosGen();
    print3DVector(WinPos);
    



    return 0;
}
