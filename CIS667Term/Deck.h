#ifndef DECK_H
#define DECK_H

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Card.h"
#define DECKSIZE 52


class Deck
{
public:
	Deck();				// Construct a deck of cards
	~Deck();			// Default destructor
	void printDeck();	// Print deck of cards
	void shuffle();
	void dealCards(std::vector<Card> &hand1, std::vector<Card> &hand2, std::vector<Card> &hand3, std::vector<Card> &hand4);
private:
	std::vector<Card> deckOfCards;
};
#endif // !DECK_H
