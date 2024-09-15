#include <bits/stdc++.h>
#include "Board.hpp"
using namespace std;
unordered_set<string> visitedStates;
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
bool isVisited(const vector<vector<string>> &board)
{
    string state = boardToString(board);
    if (visitedStates.count(state))
        return true;
    visitedStates.insert(state);
    return false;
}

void solvingN_Puzzle(Board *initialBoard, string heuristicApproach)
{
    if (!initialBoard->checkIfSolvable())
    {
        fout << "Unsolvable puzzle !!!" << endl;
        return;
    }

    stack<Board *> minimalMoves;
    int exploredBoards = 0, expandedBoards = 0;
    Board *goalBoard = NULL, *currentBoard = NULL;
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
        expandedBoards++;
        for (auto reachableBoard : currentBoard->allReachableBoards())
        {
            if (!isVisited(reachableBoard->getBoard()))
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
    exploredBoards = visitedStates.size();
    visitedStates.clear();
    fout << "Number of minimum steps by using " + heuristicApproach + ": " << minimalMoves.size() - 1 << endl;
    fout << "Number of explored boards by using " + heuristicApproach + ": " << exploredBoards << endl;
    fout << "Number of expanded boards by using " + heuristicApproach + ": " << expandedBoards << endl;
    fout << "Step by step movement:" << endl;
    while (!minimalMoves.empty())
    {
        minimalMoves.top()->printBoard();
        fout << "\n\n";
        minimalMoves.pop();
    }
}

int main()
{
    ifstream fin("input.txt");

    vector<vector<string>> board;
    int dimension;
    fin >> dimension;
    board.resize(dimension, vector<string>(dimension));
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            fin >> board[i][j];
        }
    }
    Board *puzzle = new Board(dimension, board);
    solvingN_Puzzle(puzzle, "hamming");
    solvingN_Puzzle(puzzle, "manhattan");
    delete puzzle;
}
