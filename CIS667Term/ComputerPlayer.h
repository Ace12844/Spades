#ifndef COMPUTERPLAYER_H
#pragma once
#include "AbstractPlayer.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <algorithm>
class ComputerPlayer : public AbstractPlayer
{
public:
	ComputerPlayer();
	~ComputerPlayer();
	virtual void play(Table& table, int index) override;
	virtual void makeBid() override;
	Card lowestNonSpade(std::vector<Card>::iterator first, std::vector<Card>::iterator last);
	Card highestInHandPlay(Table table);
	Card lowestOfSuit(Table table);
	Card lowestWinningOfSuit(Table table);
	bool lowestRank(Card i, Card j) { return i.getRank()<j.getRank(); }
	bool highestOfSuitInHand(Table &table);
	bool checkIfPartnerPlayed(Table table, int index);
	bool partnerPlayedHighestOfSuit(Table table, int index);
	bool partnerPlayedSecondHighest(Table table, int index);
};
#endif // !COMPUTERPLAYER_H


