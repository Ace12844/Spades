#ifndef ABSTRACTPLAYER_H
#include <iostream>
#include "Card.h"
#include "Table.h"
#include <vector>
#pragma once

class AbstractPlayer
{
public:
	AbstractPlayer();
	~AbstractPlayer();
	int getBid();
	int getTricks();
	void giveTrick();
	std::vector<Card>& getHand();
	void displayHand();
	virtual void play(Table& table, int index) = 0;
	virtual void makeBid() = 0;
	bool leadSuitInHand(int leadSuit);
	int getPartner(int index);
protected:
	std::vector<Card> _hand;
	int bid;
	int tricks;
};
#endif // !ABSTRACTPLAYER_H




