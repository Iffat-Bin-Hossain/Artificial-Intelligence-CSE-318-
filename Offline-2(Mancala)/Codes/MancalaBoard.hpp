#ifndef MANCALABOARD_HPP
#define MANCALABOARD_HPP
#include <bits/stdc++.h>
using namespace std;

class MancalaBoard
{

    const int totalBins;
    vector<int> player1Bins, player2Bins;
    int p1Store, p2Store;
    int currentTurn;
    int additionalMove1, additionalMove2;
    int captured1, captured2;
    bool isGameOver;

public:
    MancalaBoard()
        : player1Bins(6, 4), player2Bins(6, 4), p1Store(0), p2Store(0),
          currentTurn(1), totalBins(6), isGameOver(false)
    {
        additionalMove1 = additionalMove2 = captured1 = captured2 = 0;
    }
    // get functions
    vector<int> &getPlayerBins(char c)
    {
        if (c == 's')
        {
            if (currentTurn == 1)
                return player1Bins;
            else
                return player2Bins;
        }
        else
        {
            if (currentTurn == 1)
                return player2Bins;
            else
                return player1Bins;
        }
    }

    int &getPlayerStores(char c)
    {
        if (c == 's')
        {
            if (currentTurn == 1)
                return p1Store;
            else
                return p2Store;
        }
        else
        {
            if (currentTurn == 1)
                return p2Store;
            else
                return p1Store;
        }
    }
    int get_current_turn()
    {
        if (isGameOver)
            return -1;
        return currentTurn;
    }
    void checkIfGameOver()
    {
        int sum1 = accumulate(player1Bins.begin(), player1Bins.end(), 0);
        int sum2 = accumulate(player2Bins.begin(), player2Bins.end(), 0);

        if (!sum1 || !sum2)
        {

            p1Store += sum1;
            p2Store += sum2;
            isGameOver = true;
        }
    }
    int get_p1_score() { return p1Store; }
    int get_p2_score() { return p2Store; }
    int who_is_winner()
    {
        if (isGameOver)
        {
            if (p1Store == p2Store)
                return 0;
            return p1Store > p2Store ? 1 : 2;
        }
        return -1;
    }
    vector<int> get_available_moves()
    {
        if (isGameOver)
            return vector<int>();

        vector<int> &v = getPlayerBins('s');
        vector<int> availableMoves;

        for (int i = 0; i < v.size(); i++)
        {
            if (v[i] != 0)
                availableMoves.push_back(i);
        }
        return availableMoves;
    }

    int performTurn(int selected_pit)
    {
        if (isGameOver)
            return 2;

        vector<int> &self = getPlayerBins('s');
        vector<int> &opponent = getPlayerBins('o');

        if (selected_pit < 0 || selected_pit >= totalBins || self[selected_pit] == 0)
            return 1;

        int &selfStore = getPlayerStores('s');
        int &opponentStore = getPlayerStores('o');

        int stone_count_in_selected_pit = self[selected_pit];
        self[selected_pit] = 0;
        int last_stone_position = 0;

        while (stone_count_in_selected_pit > 0)
        {
            for (int i = selected_pit + 1; stone_count_in_selected_pit > 0 && i < totalBins; i++)
            {
                self[i]++;
                last_stone_position = i;
                stone_count_in_selected_pit--;
            }

            if (stone_count_in_selected_pit > 0)
            {
                selfStore++;
                last_stone_position = 6;
                stone_count_in_selected_pit--;
            }

            for (int i = 0; stone_count_in_selected_pit > 0 && i < totalBins; i++)
            {
                opponent[i]++;
                stone_count_in_selected_pit--;
                last_stone_position = 7;
            }

            for (int i = 0; stone_count_in_selected_pit > 0 && i < selected_pit + 1; i++)
            {
                self[i]++;
                stone_count_in_selected_pit--;
                last_stone_position = i;
            }
        }

        // get another turn
        if (last_stone_position != 6)
        {
            currentTurn = 3 - currentTurn;
        }
        else
        {
            if (currentTurn == 1)
                additionalMove1++;
            else
                additionalMove2++;
        }

        // if last piece falls on empty
        if (last_stone_position <= 5 && self[last_stone_position] == 1)
        {
            if (currentTurn == 1)
                captured1 += self[last_stone_position] + opponent[totalBins - last_stone_position - 1];
            else
                captured2 = self[last_stone_position] + opponent[totalBins - last_stone_position - 1];

            selfStore += self[last_stone_position] + opponent[totalBins - last_stone_position - 1];
            self[last_stone_position] = 0;
            opponent[totalBins - last_stone_position - 1] = 0;
        }

        checkIfGameOver();
        return 0;
    }

    void printBoard()
    {
        cout << "   ";
        for (int i = player2Bins.size() - 1; i >= 0; i--)
        {
            cout << setw(2) << player2Bins[i] << " ";
        }
        cout << endl;

        cout << setw(2) << p2Store
             << " " << "------------------" << " "
             << setw(-2) << p1Store
             << endl;

        cout << "   ";
        for (auto i : player1Bins)
        {
            cout << setw(2) << i << " ";
        }
        cout << endl;
    }
    friend int heuristic1(MancalaBoard &mancala, int me);
    friend int heuristic2(MancalaBoard &mancala, int me);
    friend int heuristic3(MancalaBoard &mancala, int me);
    friend int heuristic4(MancalaBoard &mancala, int me);
};
#endif