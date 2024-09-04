#ifndef BOARD_HPP
#define BOARD_HPP

#include <bits/stdc++.h>
using namespace std;

template <typename T>
void swapContent(vector<vector<T>> &twoDArray, int oldRow, int oldCol, int newRow, int newCol)
{
    T temp = twoDArray[oldRow][oldCol];
    twoDArray[oldRow][oldCol] = twoDArray[newRow][newCol];
    twoDArray[newRow][newCol] = temp;
}

class Board
{
    int dimension;
    vector<vector<string>> board;
    Board *previous;

public:
    Board()
    {
        this->previous = NULL;
    }
    Board(int dimension, vector<vector<string>> board)
    {
        this->dimension = dimension;
        this->board = board;
        this->previous = NULL;
    }
    vector<vector<string>> getBoard()
    {
        return this->board;
    }
    void setPrevious(Board *previous)
    {
        this->previous = previous;
    }
    Board *getPrevious()
    {
        return this->previous;
    }
    void printBoard()
    {
        for (int i = 0; i < dimension; ++i)
        {

            for (int j = 0; j < dimension; ++j)
            {
                cout << "+---";
            }
            cout << "+" << endl;

            for (int j = 0; j < dimension; ++j)
            {
                cout << "| " + board[i][j] + " ";
            }
            cout << "|" << endl;
        }

        for (int j = 0; j < dimension; ++j)
        {
            cout << "+---";
        }
        cout << "+" << endl;
    }

    vector<string> oneDimensionalBoard()
    {
        vector<string> linearBoard;
        for (int i = 0; i < this->dimension; i++)
        {
            for (int j = 0; j < this->dimension; j++)
            {
                linearBoard.push_back(this->board[i][j]);
            }
        }
        return linearBoard;
    }
    int findBlankPositionFromBottom()
    {
        for (int i = 0; i < this->dimension; i++)
        {
            for (int j = 0; j < this->dimension; j++)
            {
                if (board[i][j] == "*")
                {
                    return dimension - i;
                }
            }
        }
    }
    pair<int, int> findBlankPositionIndex()
    {
        for (int i = 0; i < this->dimension; i++)
        {
            for (int j = 0; j < this->dimension; j++)
            {
                if (board[i][j] == "*")
                {
                    return {i, j};
                }
            }
        }
    }
    vector<Board *> allReachableBoards()
    {
        vector<Board *> reachableBoards;
        pair<int, int> blankIndex = this->findBlankPositionIndex();
        int blankRow = blankIndex.first;
        int blankCol = blankIndex.second;

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (auto dir : directions)
        {
            int newRow = blankRow + dir.first;
            int newCol = blankCol + dir.second;

            if (newRow >= 0 && newRow < this->dimension && newCol >= 0 && newCol < this->dimension)
            {

                Board *newBoard = new Board(this->dimension, this->board);

                swapContent(newBoard->board, blankRow, blankCol, newRow, newCol);
                newBoard->setPrevious(this);
                reachableBoards.push_back(newBoard);
            }
        }

        return reachableBoards;
    }
    bool isGoalBoard()
    {
        for (int i = 0; i < this->dimension; i++)
        {
            for (int j = 0; j < this->dimension; j++)
            {
                int expectedValue = i * this->dimension + j + 1;
                if (this->board[i][j] != "*" && this->board[i][j] != to_string(expectedValue))
                {
                    return false;
                }
            }
        }
        return true;
    }

    int countInversion()
    {
        vector<string> linearBoard = this->oneDimensionalBoard();
        int totalInversion = 0;
        for (int i = 0; i < linearBoard.size() - 1; i++)
        {
            for (int j = i + 1; j < linearBoard.size(); j++)
            {
                if (linearBoard[i] != "*" && linearBoard[j] != "*")
                {
                    int num1 = std::atoi(linearBoard[i].c_str());
                    int num2 = std::atoi(linearBoard[j].c_str());
                    if (num1 > num2)
                    {
                        totalInversion++;
                    }
                }
            }
        }
        return totalInversion;
    }

    bool checkIfSolvable()
    {
        bool isSolvable;
        if (dimension % 2 != 0)
        {
            if (this->countInversion() % 2 == 0)
            {
                isSolvable = true;
            }
        }
        else
        {
            if ((this->findBlankPositionFromBottom() % 2) != (this->countInversion() % 2))
            {
                isSolvable = true;
            }
            else
            {
                isSolvable = false;
            }
        }
        return isSolvable;
    }
    int getHammingDistance()
    {
        int hammingDistance = 0;
        for (int i = 0; i < this->oneDimensionalBoard().size(); i++)
        {
            int value = atoi(this->oneDimensionalBoard().at(i).c_str());
            if (this->oneDimensionalBoard().at(i) != "*" && value != i + 1)
            {
                hammingDistance++;
            }
        }
        return hammingDistance;
    }
    int getManhattanDistance()
{
    int manhattanDistance = 0;

    
    for (int i = 0; i < this->dimension; i++)
    {
        for (int j = 0; j < this->dimension; j++)
        {
           
            int tile = atoi(board[i][j].c_str());

            
            if (tile > 0)
            {
                
                int actualRow = (tile - 1) / dimension;
                int actualColumn = (tile - 1) % dimension;

                
                manhattanDistance += abs(actualRow - i) + abs(actualColumn - j);
            }
        }
    }

    return manhattanDistance;
}

    bool isIdenticalBoard(vector<vector<string>> &newBoard)
    {
        for (int i = 0; i < this->dimension; i++)
        {
            for (int j = 0; j < this->dimension; j++)
            {
                if (this->board[i][j] != newBoard[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
};
#endif
