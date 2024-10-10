#include<bits/stdc++.h>
#include<functional>
#include "MancalaBoard.hpp"
#include "Heuristics.hpp"
using namespace std;
class Player
{
    const int maximize;
    function<int(MancalaBoard &, int)> heuristic;

public:
    Player(int maximize, function<int(MancalaBoard &, int)> heuristic)
        : maximize(maximize), heuristic(heuristic)
    {
    }
    int recursive_alpha_beta_pruning(MancalaBoard &mancala, int depth, int alpha, int beta)
    {
        if (depth == 0 || mancala.who_is_winner() != -1)
        {
            return heuristic(mancala, maximize);
        }

        if (mancala.get_current_turn() == maximize)
        {
            int value = INT32_MIN;

            vector<int> next_moves = mancala.get_available_moves();
            for (auto i : next_moves)
            {
                MancalaBoard temp(mancala);
                temp.performTurn(i);
                int node_value = recursive_alpha_beta_pruning(temp, depth - 1, alpha, beta);

                value = max(node_value, value);

                if (value >= beta)
                {
                    break;
                }
                alpha = max(alpha, value);
            }
            return value;
        }
        else
        {
            int value = INT32_MAX;
            vector<int> next_moves = mancala.get_available_moves();
            for (auto i : next_moves)
            {
                MancalaBoard temp(mancala);
                temp.performTurn(i);
                int node_value = recursive_alpha_beta_pruning(temp, depth - 1, alpha, beta);
                value = min(node_value, value);

                if (value <= alpha)
                {
                    break;
                }
                beta = min(beta, value);
            }
            return value;
        }

        cerr << "ERROR : " << __LINE__ << endl;
        return 0;
    }

    int suggest_best_move(MancalaBoard &mancala, int depth)
    {
        int alpha = INT32_MIN;
        int beta = INT32_MAX;
        int value = INT32_MIN;

        int move = -1;

        vector<int> next_moves = mancala.get_available_moves();

        for (auto i : next_moves)
        {
            MancalaBoard temp(mancala);
            temp.performTurn(i);
            int node_value = recursive_alpha_beta_pruning(temp, depth - 1, alpha, beta);

            if (node_value > value)
            {
                move = i;
            }
            value = max(node_value, value);

            alpha = max(alpha, value);
        }
        return move;
    }
};