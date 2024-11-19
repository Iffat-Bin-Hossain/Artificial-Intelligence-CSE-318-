
#include <bits/stdc++.h>
#include "MancalaBoard.hpp"
#include "Player.hpp"
using namespace std;

function<int(MancalaBoard &, int)> heuristics[5] = {
    heuristic1, heuristic1, heuristic2, heuristic3, heuristic4};

void manVscomputer(int bot, int depth)
{
    MancalaBoard mancala;
    Player player1(2, heuristics[bot]);

    mancala.printBoard();
    while (true)
    {
        int move;
        cout << "Player-" << mancala.get_current_turn() << " is playing.............." << endl;
        if (mancala.get_current_turn() == 2)
        {
            move = player1.suggest_best_move(mancala, depth);
            cout << "Computer's move : " << move << endl;
        }
        else
        {
            cout << "Your move : ";
            cin >> move;
        }

        if (move == -1)
            break;

        mancala.performTurn(move);
        mancala.printBoard();

        if (mancala.who_is_winner() != -1)
        {
            break;
        }
    }
    cout << "Player1 : " << mancala.get_p1_score() << "  |   Player2: " << mancala.get_p2_score() << endl;
    if (mancala.who_is_winner() != 0)
    {
        cout << "Player-" << mancala.who_is_winner() << " wins the match......" << endl;
    }
    else
    {
        cout << "Match Draw!!!!!!" << endl;
    }
}

MancalaBoard computerVscomputer(int heu1, int heu2, int depth, bool print = false)
{
    MancalaBoard mancala;
    Player player1(1, heuristics[heu1]);
    Player player2(2, heuristics[heu2]);

    while (true)
    {
        if (print)
        {
            mancala.printBoard();
        }

        if (mancala.get_current_turn() == 1)
        {
            if (print)
            {
                cout << "Player-1 is playing.............." << endl;
            }
            mancala.performTurn(player1.suggest_best_move(mancala, depth));
        }
        else if (mancala.get_current_turn() == 2)
        {
            if (print)
            {
                cout << "Player-2 is playing.............." << endl;
            }
            mancala.performTurn(player2.suggest_best_move(mancala, depth));
        }
        else
        {
            if (mancala.who_is_winner() != -1)
            {
                break;
            }
        }
    }
    if (print)
    {
        int winner = mancala.who_is_winner();
        cout << "Player1 : " << mancala.get_p1_score() << "  |   Player2: " << mancala.get_p2_score() << endl;

        if (winner != 0)
        {

            cout << "Player-" << winner << " wins the match......" << endl;
        }
        else
        {
            cout << "Match Draw!!!!!!" << endl;
        }
    }

    return mancala;
}

void generateReport(int depth)
{
    ofstream fout("Report.txt");
    int p1Wins = 0, p2Wins = 0;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            MancalaBoard mancala = computerVscomputer(i, j, depth);
            fout << "heuristic-" << i << " : " << " heuristic-" << j << "  =  " << mancala.get_p1_score()
                 << " : " << mancala.get_p2_score();
            if (mancala.get_p1_score() > mancala.get_p2_score())
            {
                fout << " ;Winner : Player-1" << endl;
                p1Wins++;
            }
            else if (mancala.get_p2_score() > mancala.get_p1_score())
            {
                fout << " ;Winner : Player-2" << endl;
                p2Wins++;
            }
            else
            {
                fout << " ;Winner : None" << endl;
            }
        }
    }
    fout << "\n\nPlayer-1 wins " << p1Wins << " times;Player-2 wins " << p2Wins << " times" << endl;
}

int main()
{
     //manVscomputer(2,12);
    generateReport(8);
    // MancalaBoard mancala = computerVscomputer(4, 1, 12, true);

    return 0;
}