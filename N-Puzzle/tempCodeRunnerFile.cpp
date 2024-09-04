#include <bits/stdc++.h>
#include "Board.hpp"
using namespace std;

unordered_set<string> visitedStates;

// Updated boardToString function
string boardToString(const vector<vector<string>> &board)
{
    string state = "";
    for (const auto &row : board)
    {
        for (const auto &tile : row)
        {
            state += tile + ",";
        }
    }
    return state;
}

// Updated isVisited function
bool isVisited(const vector<vector<string>> &board)
{
    string state = boardToString(board);
    if (visitedStates.count(state))
        return true;
    visitedStates.insert(state);
    return false;
}

int solvingN_Puzzle(Board *initialBoard, string heuristicApproach)
{
    if (!initialBoard->checkIfSolvable())
    {
        cout << "Unsolvable puzzle !!!" << endl;
        return -1;
    }

    stack<Board *> minimalMoves;
    Board *goalBoard = nullptr, *currentBoard = nullptr;
    priority_queue<pair<int, Board *>, vector<pair<int, Board *>>, greater<pair<int, Board *>>> pq;
    int initialHeuristic = (heuristicApproach == "hamming") ? initialBoard->getHammingDistance() : initialBoard->getManhattanDistance();
    pq.push({initialHeuristic, initialBoard});

    while (!pq.empty())
    {
        currentBoard = pq.top().second;
        int actualDistance = pq.top().first;
        pq.pop();

        if (currentBoard->isGoalBoard())
        {
            goalBoard = currentBoard;
            break;
        }

        for (auto reachableBoard : currentBoard->allReachableBoards())
        {
            if (!isVisited(reachableBoard->getBoard()) )
            {
                int newCost = actualDistance - ((heuristicApproach == "hamming") ? currentBoard->getHammingDistance() : currentBoard->getManhattanDistance()) + 1;
                pq.push({newCost + ((heuristicApproach == "hamming") ? reachableBoard->getHammingDistance() : reachableBoard->getManhattanDistance()), reachableBoard});
            }
        }
    }

    while (currentBoard != nullptr)
    {
        minimalMoves.push(currentBoard);
        currentBoard = currentBoard->getPrevious();
    }

    return minimalMoves.size() - 1;
}

int main()
{
    vector<vector<string>> board;
    int dimension;
    cin >> dimension;
    board.resize(dimension, vector<string>(dimension));
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            cin >> board[i][j];
        }
    }
    Board *puzzle = new Board(dimension, board);
    cout << solvingN_Puzzle(puzzle, "hamming") << endl;
    cout << solvingN_Puzzle(puzzle, "manhattan") << endl;
    delete puzzle;
}
