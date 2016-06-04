///////////////////////////////////////////////////////////////////////
// File: Card.h
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#pragma once
#include<string>
#include <map>
#include <iostream>
#include <set>
enum class Suit { CLUB, DIAMOND, HEART, SPADE };
enum class Face { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };



struct Card
{
	Card(Face f, Suit s) : face(f), suit(s) {}
	const Suit suit;
	const Face face;
	static const std::set<Suit> suits;
	static const std::set<Face> faces;

	static const std::map<Face, std::string> faceNames;
	static const std::map<Suit, std::string> SuitNames;

	friend std::ostream& operator<<(std::ostream& os, const Card& c);
	friend bool operator==(const Card& l, const Card& r) {
		if (r.face == l.face)
			return true;
		else
			return false;
    }
	std::string toString() const;
};


inline bool operator<(const Card & l, const Card & r)
{
	if (l.face < r.face)
		return true;
	if (l.face == r.face && l.suit < r.suit)
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& os, const Card& c);
