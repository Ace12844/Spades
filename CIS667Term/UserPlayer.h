#ifndef USERPLAYER_H
#pragma once
#include "AbstractPlayer.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
class UserPlayer : public AbstractPlayer
{
public:
	UserPlayer();
	~UserPlayer();
	virtual void play(Table& table, int index) override;
	virtual void makeBid() override;
	bool validatePlay(int leadSuit);
};
#endif // !USERPLAYER_H



