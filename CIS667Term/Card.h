#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#pragma once
class Card
{
public:
	Card();
	Card(int rank, int suit);
	~Card();
	void print() const;
	int getSuit() const;
	int getRank() const;
	int getCardValue() const;
	bool operator < (const Card& c) const;
	bool operator == (const Card& c) const;
	friend std::ostream& operator<< (std::ostream &out, const Card &card);
private:
	int _rank;
	int _suit;
};
#endif // !CARD_H
