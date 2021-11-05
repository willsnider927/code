#include "tictacSLV.hpp"

void Board::createBoard()
{
    for (int i = 0; i < 3; i++)
    {
        board.push_back({'.', '.', '.'});
    }
}

int Board::checkWin(char check)
{
    bool tie = true, winR0 = true, winR1 = true, winR2 = true, winC0 = true, winC1 = true, winC2 = true, diag1 = true, diag2 = true;
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == '.')  tie = false;
        if (board[1][i] == '.')  tie = false;
        if (board[2][i] == '.')  tie = false;
        if (board[0][i] != check) winR0 = false;
        if (board[1][i] != check) winR1 = false;
        if (board[2][i] != check) winR2 = false;
        if (board[i][0] != check) winC0 = false;
        if (board[i][1] != check) winC1 = false;
        if (board[i][2] != check) winC2 = false;
        if (board[i][i] != check) diag1 = false;
        if (board[i][2 - i] != check) diag2 = false;
    }
    return ((winR0 || winR1 || winR2 || winC0 || winC1 || winC2 || diag1 || diag2)*3) | 2*(tie) | 1;
}

int Board::makeMove()
{
    string key(1, turn);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            key.push_back(board[i][j]);
        }
    }
    if (memo[key]) return memo[key];

    int winX = checkWin('X');
    if (winX == 2)
    {
        memo[key] = 2;
        return 2;
    }
    else if (winX == 3)
    {
        memo[key] = 3;
        return 3;
    }
    int winO = checkWin('O');
    if (winO == 3)
    {
        memo[key] = 1;
        return 1;
    }
    int worst = 4;
    int best = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '.')
            {
                board[i][j] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                int score = makeMove();
                if (score < worst) worst = score;
                if (score > best) best = score;
                board[i][j] = '.';
                turn = turn == 'X' ? 'O' : 'X';
            }
        }
    }
    if (turn == 'X')
    {
        memo[key] = best;
        return best;
    }
    memo[key] = worst;
    return worst;
}

int Board::placeMoveCPU()
{
    turn = 'O';
    int best = 0;
    int temp;
    int besti, bestj;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '.')
            {
                board[i][j] = 'X';
                temp = makeMove();
                if (temp > best)
                {
                    best = temp;
                    besti = i;
                    bestj = j;
                }
                board[i][j] = '.';
            }
        }
    }
    board[besti][bestj] = 'X';
    turn = 'O';
    return checkWin('X');
}

int Board::placeMovePlayer()
{
    int i, j;
    while(1)
    {
        string row, col;
        cout << "row to place 'O'? (0-2)" << endl;
        cin >> row;
        cout << "column to place 'O'? (0-2)" << endl;
        cin >> col;
        i = stoi(row);
        j = stoi(col);
        if (board[i][j] == '.')
        {
            break;
        }
    }
    board[i][j] = 'O';
    turn = 'X';
    return checkWin('O');
}

void Board::printBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];
            if (j != 2) cout << "| ";
        }
        cout << endl;
    }
    cout << endl;
}

void Board::start()
{
    createBoard();
    cout << "Play First? [y/n]" << endl;
    string start;
    cin >> start;
    if (start == "y") turn = 'O';
    else turn = 'X';
    while (!done)
    {
        printBoard();
        if (turn == 'O') 
        {
            if(placeMovePlayer() != 1) done = true;
        }
        else 
        {
            if(placeMoveCPU() != 1) done = true;
        }
    }
    printBoard();
    turn = turn == 'X' ? 'O' : 'X'; 
    cout << "game over"<< endl;
}

int main()
{
    Board game;
    game.start();
}
