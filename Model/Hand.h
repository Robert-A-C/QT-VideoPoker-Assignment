///////////////////////////////////////////////////////////////////////
// File: Hand.h
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#pragma once
#include "Deck.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <unordered_map>

enum class PokerHand
{
    PAIR,
    TWOPAIR,
    THREEOFAKIND,
    STRAIGHT,
    FLUSH,
    FULLHOUSE,
    FOUROFAKIND,
    STRAIGHTFLUSH,
    ROYALFLUSH
};

const char* getPokerHandName(PokerHand type);

using CardPtr = std::shared_ptr<Card>;

class Hand
{
public:
    Hand();
    ~Hand();

    void clear();

    void addCard(CardPtr c);
    void removeCard(int c);
    void redrawCard(int i, CardPtr c);
    std::string handToString(int i);

    void initPayoutHands();

    void score();

    bool isDraw(int idx);
    void toggle(int idx);

    int size() const { return _hand.size(); }

    friend std::ostream& operator<<(std::ostream& os, const Hand& h);

    bool isPair();
    bool isTwoPair();
    bool isThreeOfAKind();
    bool isFourOfAKind();
    bool isFullHouse();
    bool isFlush();
    bool isStraight();
    bool isStraightFlush();
    bool isRoyalFlush();

public:
    std::unordered_map<PokerHand, int> _payoutHands;
    std::vector<CardPtr> _hand;

private:
    std::vector<bool> _draw;
};
std::ostream& operator<<(std::ostream& os, const Hand& h);



