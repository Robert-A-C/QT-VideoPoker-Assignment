///////////////////////////////////////////////////////////////////////
// File: Hand.cpp
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include <map>
#include <algorithm>


const char* getPokerHandName(PokerHand type)
{
    switch (type)
    {
    case PokerHand::PAIR: return "Pair";
    case PokerHand::TWOPAIR: return "Two Pair";
    case PokerHand::FOUROFAKIND: return "Four of a kind";
    case PokerHand::THREEOFAKIND: return "Three of a kind";
    case PokerHand::FULLHOUSE: return "Full House";
    case PokerHand::STRAIGHT: return "Straight";
    case PokerHand::FLUSH: return "Flush";
    case PokerHand::STRAIGHTFLUSH: return "Straight Flush";
    default : return "Royal Flush";
    }
}

Hand::Hand()
{
    initPayoutHands();
}


Hand::~Hand()
{
}

void Hand::clear()
{
    _hand.clear();
}

void Hand::addCard(CardPtr c)
{
    _hand.push_back(c);
    _draw.push_back(false);
}

void Hand::removeCard(int c)
{
    _hand.erase(_hand.begin() + (c - 1));
}

void Hand::redrawCard(int i, CardPtr c)
{
    _hand[i] = c;
}

std::string Hand::handToString(int i)
{
    return _hand[i]->toString();
}

void Hand::initPayoutHands()
{
    std::pair<PokerHand, bool> pair(PokerHand::PAIR, false);
    std::pair<PokerHand, bool> twoPair(PokerHand::TWOPAIR, false);
    std::pair<PokerHand, bool> threeOfAKind(PokerHand::THREEOFAKIND, false);
    std::pair<PokerHand, bool> straight(PokerHand::STRAIGHT, false);
    std::pair<PokerHand, bool> flush(PokerHand::FLUSH, false);
    std::pair<PokerHand, bool> fullHouse(PokerHand::FULLHOUSE, false);
    std::pair<PokerHand, bool> fourOfAKind(PokerHand::FOUROFAKIND, false);
    std::pair<PokerHand, bool> straightFlush(PokerHand::STRAIGHTFLUSH, false);
    std::pair<PokerHand, bool> royalFlush(PokerHand::ROYALFLUSH, false);

    _payoutHands.insert(pair);
    _payoutHands.insert(twoPair);
    _payoutHands.insert(threeOfAKind);
    _payoutHands.insert(straight);
    _payoutHands.insert(flush);
    _payoutHands.insert(fullHouse);
    _payoutHands.insert(fourOfAKind);
    _payoutHands.insert(straightFlush);
    _payoutHands.insert(royalFlush);
}


void Hand::score()
{

    if (isRoyalFlush())
        _payoutHands[PokerHand::ROYALFLUSH] = true;
    else if (isStraightFlush())
        _payoutHands[PokerHand::STRAIGHTFLUSH] = true;
    else if (isFourOfAKind())
        _payoutHands[PokerHand::FOUROFAKIND] = true;
    else if (isFullHouse())
        _payoutHands[PokerHand::FULLHOUSE] = true;
    else if (isFlush())
        _payoutHands[PokerHand::FLUSH] = true;
    else if (isStraight())
        _payoutHands[PokerHand::STRAIGHT] = true;
    else if (isThreeOfAKind())
        _payoutHands[PokerHand::THREEOFAKIND] = true;
    else if (isTwoPair())
        _payoutHands[PokerHand::TWOPAIR] = true;
    else if (isPair())
        _payoutHands[PokerHand::PAIR] = true;
}

bool Hand::isDraw(int idx)
{
    if (_draw[idx] == true)
        return true;
    else
        return false;
}

void Hand::toggle(int idx)
{
    _draw[idx - 1] = !_draw[idx - 1];
}

std::ostream& operator<<(std::ostream& os, const Hand& h)
{
    int i = 1;
    int j = 0;
    while (j < h.size()) {
        if (h._draw[j] == true)
            std::cout << i << ") " << *h._hand[j] << " (draw)" << std::endl;
        else
            std::cout << i << ") " << *h._hand[j] << " (hold)" << std::endl;

        i++;
        j++;

    }

    return os;
}


bool Hand::isPair()
{
    bool isPair = false;



    std::map<Face, int> h;


        for (int i = 0; i < _hand.size(); i++)
        {
            if(_hand[i]->face == Face::KING || _hand[i]->face == Face::QUEEN || _hand[i]->face == Face::JACK || _hand[i]->face == Face::ACE)
            h[_hand[i]->face]++;
        }

        int pairCount = count_if(h.begin(), h.end(), [](std::pair<Face, int> e) {return (e.second == 2); });
        if (pairCount == 1)
        {
            isPair = true;
        }

        return isPair;

}

bool Hand::isTwoPair()
{
    bool isTwoPair = false;



    std::map<Face, int> h;


    for (int i = 0; i < _hand.size(); i++)
    {
        h[_hand[i]->face]++;
    }

    int pairCount = count_if(h.begin(), h.end(), [](std::pair<Face, int> e) {return (e.second == 2); });
    if (pairCount > 1)
    {
        isTwoPair = true;
    }

    return isTwoPair;

}

bool Hand::isThreeOfAKind()
{
    bool isThree = false;



    std::map<Face, int> h;

        for (int i = 0; i < _hand.size(); i++)
        {
            h[_hand[i]->face]++;
        }

        int threeCount = count_if(h.begin(), h.end(), [](std::pair<Face, int> e) {return (e.second == 3); });
        if (threeCount > 0)
        {
            isThree = true;
        }

        return isThree;

}

bool Hand::isFourOfAKind()
{
    bool isFour = false;



    std::map<Face, int> h;



        for (int i = 0; i < _hand.size(); i++)
        {
            h[_hand[i]->face]++;
        }

        int fourCount = count_if(h.begin(), h.end(), [](std::pair<Face, int> e) {return (e.second == 4); });
        if (fourCount > 0)
        {
            isFour = true;
        }

        return isFour;
}



bool Hand::isFullHouse()
{
    return(isPair() && isThreeOfAKind());
}

bool Hand::isFlush()
{
    bool isFlush = false;



    std::set<Suit> h;



    for (int i = 0; i < _hand.size(); i++)
    {
        h.insert(_hand[i]->suit);
    }


    if (h.size() == 1)
    {
        isFlush = true;
    }

    return isFlush;
}

bool Hand::isStraight()
{
    bool isStraight = false;



    std::set<int> h;


    for (int i = 0; i < _hand.size(); i++)
    {
        h.insert((int)_hand[i]->face);
    }

    auto first = h.begin();
    auto last = h.end();

    last--;

    if (h.size() == 5)
    {
        if (*first == (*last - 4))
        {
            isStraight = true;
        }
    }

    if (*first == 0)
    {
        h.insert(13);
    }

    last++;

    if (h.size() == 6)
    {
        *first++;
        if (*first == (*last - 4))
        {
            isStraight = true;
        }
    }

    return isStraight;
}

bool Hand::isStraightFlush()
{
    return(isStraight() && isFlush());
}

bool Hand::isRoyalFlush()
{
    bool isRF = false;

    std::set<int> h;

    if (isStraightFlush())
    {
        for (int i = 0; i < _hand.size(); i++)
        {
            h.insert((int)_hand[i]->face);
        }
    }

    auto start = h.begin();

    if (h.size() == 5)
    {
        if (*start == 0)
        {
            h.insert(13);
        }

        auto last = h.end();
        last--;

        if (*last == 13)
        {
            last--;
            if (*last == 12)
            {
                isRF = true;
            }
        }
    }


    return isRF;
}
