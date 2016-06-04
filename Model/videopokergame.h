///////////////////////////////////////////////////////////////////////
// File: videopokergame.h
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#pragma once
#include <unordered_map>
#include "Hand.h"
#include "Deck.h"

class Hand;
class Deck;

class videopokergame
{
public:
    videopokergame();
    ~videopokergame();

    std::string drawHand(int i);    // draw hand
    void newCards(int i);           // draws new cards
    void newHand();                 // deals new hand
    std::string winCheck();         // checks for win

private:
    void initPayouts();             // Map of payout and credit values
    std::string outcome(Hand hand); // Checks for hand outcome

private:
    int credits = 0;
    std::unordered_map<PokerHand, int> _payout;
    std::vector<int> _choices;

    Deck deck;
    Hand _pokerHand;

};
