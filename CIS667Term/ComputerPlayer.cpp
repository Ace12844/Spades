#include "ComputerPlayer.h"
//#define TEST_COMPUTERPLAYER

ComputerPlayer::ComputerPlayer()
{
	bid = 0;
	tricks = 0;
}


ComputerPlayer::~ComputerPlayer()
{
}

void ComputerPlayer::makeBid()
{
	bid = 0;					// reinitialize bid to zero before a bid is made
	tricks = 0;					// tricks will be reinitialized before bid is made and hand is played
	for (auto& c : _hand)
	{
		if (c.getRank() >= 10)
		{
			bid++;
		}
	}
}

Card ComputerPlayer::lowestNonSpade(std::vector<Card>::iterator first, std::vector<Card>::iterator last)
{
	if (first == last) return *last;
	std::vector<Card>::iterator smallest = first;

	while (++first != last)
		if (first->getRank() < smallest->getRank() && first->getSuit() != 4)
			smallest = first;
	return *smallest;
}

void ComputerPlayer::play(Table& table, int index)
{
	//int p;
	//bool find_spade = false;
	//bool find = false;
	//// If lead suit is 0 means that there hasnt been a card played so select best option from hand
	//
	//// Look at history of played cards to make best selection
	//if (table.getLeadSuit() == 0)			// THIS FUNCTION PLAYS ANY CARD RIGHT NOW
	//{

	//	// Look at history of played cards and play best choice
	//		

	//	p = rand() % _hand.size();
	//	table.addCard(_hand[p], index);
	//	_hand.erase(_hand.begin() + p);		// Remove card from hand
	//	std::this_thread::sleep_for(std::chrono::seconds(3));
	//}
	//else									
	//{
	//	// Check if partner has played a card first

	//		// If partner is winning, avoid using a spade and throw off lowest "ranked" card in hand that is not a spade unless hand is only spades

	//		// If partner is not winning then cut with lowest winning spade

	//	// If partner has not played, make best selection based on lead suit and history of played cards
	//	for (int x = 0; x < _hand.size(); x++)
	//	{
	//		if (_hand[x].getSuit() == table.getLeadSuit())
	//		{
	//			table.addCard(_hand[x], index);
	//			_hand.erase(_hand.begin() + x);
	//			find = true;
	//			break;
	//		}
	//	}
	//	if (!find)							// If suit was not found then a spade is looked for first
	//	{
	//		for (int x = 0; x < _hand.size(); x++)
	//		{
	//			if (_hand[x].getSuit() == 4)			// Spade was found in hand
	//			{
	//				table.addCard(_hand[x], index);
	//				_hand.erase(_hand.begin() + x);
	//				find_spade = true;
	//				if (table.canLeadWithSpade() == false)		// Check to see if flag to allow leading with spade is false. Allowing a player to cut triggers this rule to be set to true
	//					table.allowCut();
	//				break;
	//			}
	//		}
	//		if (!find_spade)					// No spade found in hand. Play any card FOR NOW
	//		{
	//			p = rand() % _hand.size();
	//			table.addCard(_hand[p], index);
	//			_hand.erase(_hand.begin() + p);
	//		}
	//	}
	//}
	
	// If last card in hand play it no matter what
	if (_hand.size() == 1) {
		table.addCard(_hand[0], index);
		_hand.erase(_hand.begin());		// Remove card from hand
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return;
	}
	// Check if lead suit = 0. This means there is no card on the table and the player can lead
	if (table.getLeadSuit() == 0)
	{
		// If hand is all spades play first card in hand regardless if flag is set. Set flag for leading with spades if not set
		if (_hand.begin()->getSuit() == 4) {			// Since hand is sorted by suit then rank, if the first card in hand's suit is spades the entire hand is spades
			table.addCard(_hand[0], index);
			_hand.erase(_hand.begin());		// Remove card from hand
			std::this_thread::sleep_for(std::chrono::seconds(3));
			if (table.canLeadWithSpade() == false)
				table.allowCut();
			return;
		}
		// Check if highest available of any suit other than spades is in hand
		for (auto& c : _hand)
		{
			// card value == availableCards[leadSuit][0] value and the suit != spades then this is highest of suit available
			if ((c.getCardValue() == table.getRemainingCards()[c.getSuit()].begin()->getCardValue()) && c.getSuit() != 4)
			{
				// Highest card of a suit is in hand so play it
				table.addCard(c, index);
				_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());	// Remove card from hand
				std::this_thread::sleep_for(std::chrono::seconds(3));
				return;
			}
		}

		// Highest card of any suit is not in hand so play lowest ranked card of any suit other than spades in hand
		table.addCard(lowestNonSpade(_hand.begin(), _hand.end()), index);
		_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return;
	}
	// Lead suit is not 0 so there are cards on the table since lead suit has been set
	else
	{
		// Check if lead suit is in hand
		if (leadSuitInHand(table.getLeadSuit()))
		{
			// Partner has played
			if (table.getTable()[getPartner(index)].getCardValue() != 0)
			{
				// Player’s partner winning
				if (getPartner(index) == table.getWinner())
				{
					// Partners card is highest availabe of suit
					if (table.getRemainingCards()[table.getLeadSuit()].begin()->getCardValue() == table.getTable()[getPartner(index)].getCardValue())
					{
						// Play lowest rank of suit in hand
						for (auto& c : _hand)
						{
							if (c.getSuit() == table.getLeadSuit())
							{
								table.addCard(c, index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
						}
					}
					// Partners card is not highest on table
					else
					{
						// Check if highest available of any suit other than spades is in hand
						for (auto& c : _hand)
						{
							// card value == availableCards[leadSuit][0] card value this is highest of suit available
							if ((c.getCardValue() == table.getRemainingCards()[table.getLeadSuit()].begin()->getCardValue()))
							{
								// There are more than one possible card left of the suit
								if (table.getRemainingCards()[table.getLeadSuit()].size() != 1)
								{
									// If player's partner card is the second highest on the table and highest is in hand, throw lowest card available of suit
									if (table.getTable()[getPartner(index)].getCardValue() == table.getRemainingCards()[table.getLeadSuit()][1].getCardValue())
									{
										// Get lowest available of suit and play. Can be the highest card
										for (auto& lowest : _hand)
										{
											if (lowest.getSuit() == table.getLeadSuit())
											{
												table.addCard(lowest, index);
												_hand.erase(std::remove(_hand.begin(), _hand.end(), lowest), _hand.end());
												std::this_thread::sleep_for(std::chrono::seconds(3));
												return;
											}
										}
									}
									// Partner does not have second highest card
									else
									{
										// Play highest card of suit since in hand. Currently c
										table.addCard(c, index);
										_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
										std::this_thread::sleep_for(std::chrono::seconds(3));
										return;
									}
								}
							}
						}
						// For each loop can go through entire list and not find any of the highest card of suit in hand so immediately play lowest of suit possible
						for (auto& c : _hand)
						{
							if (c.getSuit() == table.getLeadSuit())
							{
								table.addCard(c, index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
						}
					}
				}
				// Player’s partner is not winning
				else
				{
					// Check if highest card of suit in hand
					for (auto& c : _hand)
					{
						if (c.getCardValue() == table.getRemainingCards()[table.getLeadSuit()].begin()->getCardValue())
						{
							table.addCard(c, index);
							_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
							std::this_thread::sleep_for(std::chrono::seconds(3));
							return;
						}
					}
					// Check if highest card of lead suit is on table
					if (table.getTableHigh() == table.getRemainingCards()[table.getLeadSuit()].begin()->getCardValue())
					{
						// Play lowest of suit
						for (auto& c : _hand)
						{
							if (c.getSuit() == table.getLeadSuit())
							{
								table.addCard(c, index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
						}
					}
					// Highest card of suit is not on table and not in hand
					else
					{
						// Play lowest “winning” ranked card of suit in hand
						for (auto& c : _hand)
						{
							if (c.getSuit() == table.getLeadSuit() && c.getCardValue() > table.getTableHigh())
							{
								table.addCard(c, index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
						}
						// No cards can beat winning card of suit. Play lowest card of suit
						for (auto& c : _hand)
						{
							if (c.getSuit() == table.getLeadSuit())
							{
								table.addCard(c, index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
						}
					}	
				}
			}
			// Partner didn't play
			else
			{
				// Check if highest card of lead suit is on table
				if (table.getTableHigh() == table.getRemainingCards()[table.getLeadSuit()].begin()->getCardValue())
				{
					// Play lowest of suit
					for (auto& c : _hand)
					{
						if (c.getSuit() == table.getLeadSuit())
						{
							table.addCard(c, index);
							_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
							std::this_thread::sleep_for(std::chrono::seconds(3));
							return;
						}
					}
				}
				// Check if highest card of suit in hand
				for (auto& c : _hand)
				{
					if (c.getCardValue() == table.getRemainingCards()[table.getLeadSuit()].begin()->getCardValue())
					{
						table.addCard(c, index);
						_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
						std::this_thread::sleep_for(std::chrono::seconds(3));
						return;
					}
				}
				// Highest card of lead suit is not in hand and not on the table

				// Play lowest “winning” ranked card of suit in hand
				for (auto& c : _hand)
				{
					if (c.getSuit() == table.getLeadSuit() && c.getCardValue() > table.getTableHigh())
					{
						table.addCard(c, index);
						_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
						std::this_thread::sleep_for(std::chrono::seconds(3));
						return;
					}
				}
				// No cards can beat winning card of suit. Play lowest card of suit
				for (auto& c : _hand)
				{
					if (c.getSuit() == table.getLeadSuit())
					{
						table.addCard(c, index);
						_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
						std::this_thread::sleep_for(std::chrono::seconds(3));
						return;
					}
				}
			}
		}
		// Lead suit is not in players hand
		else
		{
			// Partner is winning
			if (getPartner(index) == table.getWinner())
			{
				// If player’s hand contains all spades throw lowest spade
				if (_hand.begin()->getSuit() == 4) {

					table.addCard(*_hand.begin(), index);
					_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
					std::this_thread::sleep_for(std::chrono::seconds(3));
					return;
				}

				// Players hand does not contain all spades. Play lowest ranked card of any suit other than spades
				table.addCard(lowestNonSpade(_hand.begin(), _hand.end()), index);
				_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
				std::this_thread::sleep_for(std::chrono::seconds(3));
				return;
			}
			// Partner is not winning
			else
			{
				// If winning card is a spade, play lowest winning spade
				if (table.getTable()[table.getWinner()].getSuit() == 4)
				{
					for (auto& c : _hand)
					{
						if (c.getSuit() == 4 && c.getCardValue() > table.getTableHigh())
						{
							table.addCard(c, index);
							_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
							std::this_thread::sleep_for(std::chrono::seconds(3));
							return;
						}
					}

					// If player cannot play "lowest winning spade" and hand contains all spades, play lowest
					if (_hand.begin()->getSuit() == 4)
					{
						table.addCard(*_hand.begin(), index);
						_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
						std::this_thread::sleep_for(std::chrono::seconds(3));
						return;
					}

					// If the "lowest winning spade" is not possible, play lowest card of any suit
					table.addCard(lowestNonSpade(_hand.begin(), _hand.end()), index);
					_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
					std::this_thread::sleep_for(std::chrono::seconds(3));
					return;
				}
				// Winning card is not a spade so either play lowest spade or lowest ranked card in hand if player does not have spades in hand
				else
				{
					// Throw lowest available spade
					for (auto& c : _hand) 
					{
						if (c.getSuit() == 4) 
						{
							table.addCard(c, index);
							_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
							std::this_thread::sleep_for(std::chrono::seconds(3));
							return;
						}
					}
						// Player cannot play lowest available spade and win trick so throw lowest ranked card in hand that is not spades
						table.addCard(lowestNonSpade(_hand.begin(), _hand.end()), index);
						_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
						std::this_thread::sleep_for(std::chrono::seconds(3));
						return;
				}
			}	
		}
	}
}


#ifdef TEST_COMPUTERPLAYER
#include "Deck.h"
void main()
{
	ComputerPlayer comp;
	comp.makeBid();
	std::cout << comp.getBid() << std::endl;
}
#endif // TEST_COMPUTERPLAYER
