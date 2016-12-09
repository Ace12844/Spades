#ifndef GAME_H
#include "Deck.h"
#include "Table.h"
#include "ComputerPlayer.h"
#include "UserPlayer.h"
#pragma once
class Game
{
public:
	Game(const Game& game) = delete;
	Game& operator=(const Game& game) = delete;
	Game(Deck& d, Table& t, ComputerPlayer& c1, ComputerPlayer& c2, ComputerPlayer& c3, UserPlayer& u) : deck(d), table(t), comp1(c1), comp2(c2), comp3(c3), user(u) 
	{
		handCount = 0; teamOneScore = 0; teamTwoScore = 0; winner = -1;
	}
	~Game();
	void playGame();
	void dealCards(int dealer);
	void bid(int dealer);
	void play(int winner);
	void awardTrick(int winner);
	void sortHands();
	void displayHands();
private:
	Game();		// remove default constructor and also keep friend classes from invoking the default constructor
	Deck& deck;
	Table& table;
	ComputerPlayer comp1;
	ComputerPlayer comp2;
	ComputerPlayer comp3;
	UserPlayer user;
	int handCount;
	int teamOneScore;
	int teamTwoScore;
	int winner;
};
#endif // !GAME_H