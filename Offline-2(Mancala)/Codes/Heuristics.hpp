#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include <bits/stdc++.h>
#include "MancalaBoard.hpp"
using namespace std;


int heuristic1(MancalaBoard &mancala, int me)
{
    if (me == 1)
    {
        return mancala.p1Store - mancala.p2Store;
    }
    else
    {
        return mancala.p2Store - mancala.p1Store;
    }
}

int heuristic2(MancalaBoard &mancala, int me)
{
    int sum1 = accumulate(mancala.player1Bins.begin(), mancala.player1Bins.end(), 0);
    int sum2 = accumulate(mancala.player2Bins.begin(), mancala.player2Bins.end(), 0);

    int w1 = 10, w2 = 20;
    if (me == 1)
    {
        return w1 * (mancala.p1Store - mancala.p2Store) + w2 * (sum1 - sum2);
    }
    else
    {
        return w1 * (mancala.p2Store - mancala.p1Store) + w2 * (sum2 - sum1);
    }
}

int heuristic3(MancalaBoard &mancala, int me)
{
    int sum1 = accumulate(mancala.player1Bins.begin(), mancala.player1Bins.end(), 0);
    int sum2 = accumulate(mancala.player2Bins.begin(), mancala.player2Bins.end(), 0);

    int w1 = 10, w2 = 20, w3 = 30;
    if (me == 1)
    {
        return w1 * (mancala.p1Store - mancala.p2Store) + w2 * (sum1 - sum2) + w3 * mancala.additionalMove1;
    }
    else
    {
        return w1 * (mancala.p2Store - mancala.p1Store) + w2 * (sum2 - sum1) + w3 * mancala.additionalMove2;
    }
}

int heuristic4(MancalaBoard &mancala, int me)
{
    int sum1 = accumulate(mancala.player1Bins.begin(), mancala.player1Bins.end(), 0);
    int sum2 = accumulate(mancala.player2Bins.begin(), mancala.player2Bins.end(), 0);

    int w1 = 10, w2 = 20, w3 = 30, w4 = 40;
    if (me == 1)
    {
        return w1 * (mancala.p1Store - mancala.p2Store) + w2 * (sum1 - sum2) + w3 * mancala.additionalMove1 + w4 * mancala.captured1;
    }
    else
    {
        return w1 * (mancala.p2Store - mancala.p1Store) + w2 * (sum2 - sum1) + w3 * mancala.additionalMove2 + w4 * mancala.captured2;
    }
}




#endif 
