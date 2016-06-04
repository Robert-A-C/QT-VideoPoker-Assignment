///////////////////////////////////////////////////////////////////////
// File: Deck.cpp
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#include "Deck.h"
#include "Card.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Deck::Deck()
{
	srand(static_cast<unsigned int>(time(0)));
	if (_deck.size() != 0)
		_deck.clear();

	for (auto f : Card::faces)
		for (auto s : Card::suits)
			_deck.push_back(std::make_shared<Card>(Card(f, s)));

	_topOfDeck = _deck.size() - 1;


}

bool Deck::isEmpty() const
{
	return (_topOfDeck < 0);
}

CardPtr Deck::draw()
{
	return _deck.at(_topOfDeck--);
}

Card Deck::cut()
{
	return *_deck[rand() % _deck.size()];
}

void Deck::shuffle()
{
	int j = 0;
	for (int i = 0; i < 9000; ++i)
	{
		swap(_deck[j], _deck[ j + (rand() % (_deck.size()-j))]);
		j++;
		if (j == 52)
			j = 0;
	}
}

void Deck::sort()
{
	std::sort(_deck.begin(), _deck.end(), [](CardPtr lhs, CardPtr rhs) {return (*lhs < *rhs); });
}



