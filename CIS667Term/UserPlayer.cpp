#include "UserPlayer.h"



UserPlayer::UserPlayer()
{
}


UserPlayer::~UserPlayer()
{
}

void UserPlayer::play(Table& table, int index = 0)
{
	int selection;
	tricks = 0;		// reinitialize tricks to zero before bid is made and hand is played
	std::cout << "What card would you like to play? (Please use 1 - " << _hand.size() << " to make card selection) ";
	std::cin >> selection;
	while (!(selection < 1 || selection > _hand.size()) && !validatePlay(table.getLeadSuit()) && _hand[selection - 1].getSuit() != table.getLeadSuit())
	{
		std::cout << "Invalid choice! Please select a valid card? (Please use 1 - " << _hand.size() << " to make card selection) ";
		std::cin >> selection;
	}
	table.addCard(_hand[selection-1], 0);
	_hand.erase(_hand.begin() + selection - 1);
}

void UserPlayer::makeBid()
{
	std::cout << "How much do you bid? (0-13) ";
	std::cin >> bid;
	while ((bid < 0 || bid > 13))
	{
		std::cout << "Please bid within range (0-13) ";
		std::cin >> bid;
	} 
	std::cout << std::endl;
}

// checks if lead suit is in hand and if it is then the play is not valid
bool UserPlayer::validatePlay(int leadSuit)
{
	for (auto& c : _hand)
	{
		if (c.getSuit() == leadSuit)
			return false;
	}
	return true;
}