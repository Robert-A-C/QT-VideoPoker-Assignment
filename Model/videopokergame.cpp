///////////////////////////////////////////////////////////////////////
// File: videopokergame.cpp
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#include "videopokergame.h"
#include "Deck.h"
#include "Hand.h"
#include <string>



videopokergame::videopokergame()
{
    initPayouts();

    deck.shuffle();
    while (_pokerHand._hand.size() != 5) // fills the hand with cards until hand is full
    {
        _pokerHand.addCard(deck.draw());
    }
}

videopokergame::~videopokergame()
{
}

void videopokergame::newHand() // deals new hand
{
    _pokerHand.clear();
    deck.shuffle();
    while (_pokerHand._hand.size() != 5)
    {
        _pokerHand.addCard(deck.draw());
    }
}

std::string videopokergame::drawHand(int i)
{
    std::string card = _pokerHand.handToString(i);
    return card;
}

std::string videopokergame::winCheck() // checks for a winning hand
{
    _pokerHand.score();
    std::string result = outcome(_pokerHand);
    return result;
}

void videopokergame::initPayouts() // Map of payout and credit values
{
    std::pair<PokerHand, int> pair(PokerHand::PAIR, 1);
    std::pair<PokerHand, int> twoPair(PokerHand::TWOPAIR, 2);
    std::pair<PokerHand, int> threeOfAKind(PokerHand::THREEOFAKIND, 3);
    std::pair<PokerHand, int> straight(PokerHand::STRAIGHT, 4);
    std::pair<PokerHand, int> flush(PokerHand::FLUSH, 6);
    std::pair<PokerHand, int> fullHouse(PokerHand::FULLHOUSE, 9);
    std::pair<PokerHand, int> fourOfAKind(PokerHand::FOUROFAKIND, 25);
    std::pair<PokerHand, int> straightFlush(PokerHand::STRAIGHTFLUSH, 50);
    std::pair<PokerHand, int> royalFlush(PokerHand::ROYALFLUSH, 250);

    _payout.insert(pair);
    _payout.insert(twoPair);
    _payout.insert(threeOfAKind);
    _payout.insert(straight);
    _payout.insert(flush);
    _payout.insert(fullHouse);
    _payout.insert(fourOfAKind);
    _payout.insert(straightFlush);
    _payout.insert(royalFlush);
}

void videopokergame::newCards(int i) // draws new cards
{
    _pokerHand.redrawCard(i, deck.draw());
}

std::string videopokergame::outcome(Hand hand) // Checks for hand outcome
{
    std::string outcome;

    auto end = hand._payoutHands.end();
    end--;
    for (auto h : hand._payoutHands)
    {
        auto p = _payout.begin();

        if (h.second == true)
        {
            while (p->first != h.first)
            p++;

            outcome.append("You got a ");
            outcome.append(getPokerHandName(h.first));
            outcome.append("! You won ");
            outcome.append(std::to_string(p->second));
            outcome.append(" credits!\n");
            credits = credits + p->second;
            break;
        }
        else if (h.first == end->first)
        {
            outcome.append("No payout hands!\n");
        }
    }

    return outcome;
}
