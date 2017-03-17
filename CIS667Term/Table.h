#ifndef TABLE_H
#define TABLE_H

#include "Card.h"
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <map>
#include <queue>
#pragma once
class Table
{
public:
	Table();
	~Table();
	void addCard(Card card, int idx);
	int getWinner();
	void clearTable();
	void display();
	int getLeadSuit();
	std::vector<Card> getTable();
	void allowCut();
	void resetLeadWithSpade();
	bool canLeadWithSpade();
	bool moreThanOneLeft(int leadSuit);
	bool highestOfSuitPlayed();
	std::map<int, std::vector<Card> > getRemainingCards();
	int getTableHigh();
	void resetAvailableCard();
	void clearPlayedCards();
	void displayWinner();
private:
	std::vector<Card> table;
	std::map<int, std::vector<Card> > remainingCards;
	int topCardIdx;
	int tableHigh;
	int _leadSuit;
	bool leadWithSpade;
};
#endif // !TABLE_H
