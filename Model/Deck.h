///////////////////////////////////////////////////////////////////////
// File: Deck.h
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#pragma once
#include "Card.h"
#include <memory>
#include <vector>
struct Card;
using CardPtr = std::shared_ptr<Card>;


class Deck
{
public:
	Deck();

	bool isEmpty() const;
	CardPtr draw();
	Card cut();
	void shuffle();
	void sort();



private:
	std::vector<CardPtr> _deck;
	int _topOfDeck;
};

