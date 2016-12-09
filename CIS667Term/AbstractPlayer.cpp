#include "AbstractPlayer.h"

AbstractPlayer::AbstractPlayer()
{
}

AbstractPlayer::~AbstractPlayer()
{
}

int AbstractPlayer::getBid()
{
	return bid;
}

int AbstractPlayer::getTricks()
{
	return tricks;
}

void AbstractPlayer::giveTrick()
{
	tricks++;
}

std::vector<Card>& AbstractPlayer::getHand()
{
	return _hand;
}

void AbstractPlayer::displayHand()
{
	for (auto& c : _hand)
	{
		std::cout << c;
	}
	std::cout << std::endl;
}

bool AbstractPlayer::leadSuitInHand(int leadSuit)
{
	for (auto& c : _hand) 
	{
		if (c.getSuit() == leadSuit)
			return true;
	}
	return false;
}

int AbstractPlayer::getPartner(int index)
{
	switch (index)
	{
	case 0:
		return 2;
		break;
	case 1:
		return 3;
		break;
	case 2:
		return 0;
		break;
	case 3:
		return 1;
		break;
	default:
		break;
	}
}

