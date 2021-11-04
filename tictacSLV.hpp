#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;
class Board
{
    private:
        vector<vector<char>> board;
        char turn;
        bool done = false;
        map<string,int> memo;
    public:
        void createBoard();
        int checkWin(char check);
        int makeMove();
        int placeMoveCPU();
        int placeMovePlayer();
        void printBoard();
        void start();
};