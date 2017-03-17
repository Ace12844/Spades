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

Card ComputerPlayer::highestInHandPlay(Table table)
{
	Card high;
	for (auto& c : _hand)
	{
		// card value == availableCards[leadSuit][0] value and the suit != spades then this is highest of suit available
		if ((c.getCardValue() == table.getRemainingCards()[c.getSuit()].begin()->getCardValue()) && c.getSuit() != 4)
		{
			// Highest card of a suit is in hand so play it
			high = c;
		}
	}
	return high;
}

Card ComputerPlayer::lowestOfSuit(Table table)
{
	Card lowSuit;

	for (auto& c : _hand)
	{
		if (c.getSuit() == table.getLeadSuit())
		{
			lowSuit = c;
		}
	}
	return lowSuit;
}

Card ComputerPlayer::lowestWinningOfSuit(Table table)
{
	Card lowWinner;

	for (auto& c : _hand)
	{
		if (c.getSuit() == table.getLeadSuit() && c.getCardValue() > table.getTableHigh())
		{
			lowWinner = c;
		}
	}

	return lowWinner;
}

bool ComputerPlayer::highestOfSuitInHand(Table &table)
{
	for (auto& c : _hand)
	{
		// card value == availableCards[leadSuit][0] value and the suit != spades then this is highest of suit available
		if ((c.getCardValue() == table.getRemainingCards()[c.getSuit()].begin()->getCardValue()) && c.getSuit() != 4)
		{
			return true;
		}
	}
	return false;
}

bool ComputerPlayer::checkIfPartnerPlayed(Table table, int index)
{
	return table.getTable()[getPartner(index)].getCardValue() != 0;
}

bool ComputerPlayer::partnerPlayedHighestOfSuit(Table table, int index)
{
	return table.getRemainingCards()[table.getLeadSuit()].begin()->getCardValue() == table.getTable()[getPartner(index)].getCardValue();
}

bool ComputerPlayer::partnerPlayedSecondHighest(Table table, int index)
{
	if (!table.moreThanOneLeft(table.getLeadSuit()))
		return false;
	else
		return table.getTable()[getPartner(index)].getCardValue() == table.getRemainingCards()[table.getLeadSuit()][1].getCardValue();
}

void ComputerPlayer::play(Table& table, int index)
{	
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
		// Since hand is sorted by suit then rank, if the first card in hand's suit is spades										
		// the entire hand is spades. Since lead suit hasn't been set then this player can 
		// lead with spades
		if (_hand.begin()->getSuit() == 4) {			
			table.addCard(_hand[0], index);
			_hand.erase(_hand.begin());		// Remove card from hand
			std::this_thread::sleep_for(std::chrono::seconds(3));
			if (!table.canLeadWithSpade())
				table.allowCut();
			return;
		}

		if (highestOfSuitInHand(table))
		{
			table.addCard(highestInHandPlay(table), index);
			_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}

		// Highest card of any suit is not in hand so play lowest ranked card of any suit other than spades in hand
		if (table.getTable()[index].getCardValue() == 0)
		{
			table.addCard(lowestNonSpade(_hand.begin(), _hand.end()), index);
			_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
			std::this_thread::sleep_for(std::chrono::seconds(3));
			return;
		}
	}
	// Lead suit has been set, so there are cards on the table
	else
	{
		// Check if lead suit is in hand
		if (leadSuitInHand(table.getLeadSuit()))
		{
			// Partner has played
			if (checkIfPartnerPlayed(table, index))
			{
				// Player’s partner winning
				if (getPartner(index) == table.getWinner())
				{
					// Partners card is highest available of suit
					if (partnerPlayedHighestOfSuit(table, index))
					{
						// Play lowest of suit in hand
						table.addCard(lowestOfSuit(table), index);
						_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
						std::this_thread::sleep_for(std::chrono::seconds(3));
						return;
					}
					// Partners card is not highest on table
					else
					{
						// Check if player has highest card of lead suit in hand
						if (highestOfSuitInHand(table))
						{
							// There are more than one possible card of the lead suit left && partner has played second highest
							if (partnerPlayedSecondHighest(table, index))
							{
								table.addCard(lowestOfSuit(table), index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
							// Partner did not play second highest so play highest card of lead suit
							else
							{
								table.addCard(highestInHandPlay(table), index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
						}
						// Partner did not play highest and player does not have highest of lead suit in hand so play lowest of suit
						else
						{
							table.addCard(lowestOfSuit(table), index);
							_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
							std::this_thread::sleep_for(std::chrono::seconds(3));
							return;
						}
						// Check if highest available of any suit other than spades is in hand
						//for (auto& c : _hand)
						//{
						//	// card value == availableCards[leadSuit][0] card value this is highest of suit available
						//	if ((c.getCardValue() == table.getRemainingCards()[table.getLeadSuit()].begin()->getCardValue()))
						//	{
						//		// There are more than one possible card left of the suit
						//		if (table.getRemainingCards()[table.getLeadSuit()].size() != 1)
						//		{
						//			// If player's partner card is the second highest on the table and highest is in hand, throw lowest card available of suit
						//			if (table.getTable()[getPartner(index)].getCardValue() == table.getRemainingCards()[table.getLeadSuit()][1].getCardValue())
						//			{
						//				// Get lowest available of suit and play. Can be the highest card
						//				for (auto& lowest : _hand)
						//				{
						//					if (lowest.getSuit() == table.getLeadSuit())
						//					{
						//						table.addCard(lowest, index);
						//						_hand.erase(std::remove(_hand.begin(), _hand.end(), lowest), _hand.end());
						//						std::this_thread::sleep_for(std::chrono::seconds(3));
						//						return;
						//					}
						//				}
						//			}
						//			// Partner does not have second highest card
						//			else
						//			{
						//				// Play highest card of suit since in hand. Currently c
						//				table.addCard(c, index);
						//				_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
						//				std::this_thread::sleep_for(std::chrono::seconds(3));
						//				return;
						//			}
						//		}
						//	}
						//}
						
						// For each loop can go through entire list and not find any of the highest card of suit in hand so immediately play lowest of suit possible
						/*for (auto& c : _hand)
						{
							if (c.getSuit() == table.getLeadSuit())
							{
								table.addCard(c, index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
						}*/
					}
				}
				// Player’s partner is not winning
				else
				{
					// If highest of lead suit is in hand, play it
					if (highestOfSuitInHand(table))
					{
						table.addCard(highestInHandPlay(table), index);
						_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
						std::this_thread::sleep_for(std::chrono::seconds(3));
					}

					/*for (auto& c : _hand)
					{
						if (c.getCardValue() == table.getRemainingCards()[table.getLeadSuit()].begin()->getCardValue())
						{
							table.addCard(c, index);
							_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
							std::this_thread::sleep_for(std::chrono::seconds(3));
							return;
						}
					}*/

					// If highest card of lead suit is on table, play lowest of suit
					if (table.highestOfSuitPlayed())
					{
						table.addCard(lowestOfSuit(table), index);
						_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
						std::this_thread::sleep_for(std::chrono::seconds(3));
						return;

						// Play lowest of suit
						/*for (auto& c : _hand)
						{
							if (c.getSuit() == table.getLeadSuit())
							{
								table.addCard(c, index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
						}*/
					}
					// Highest card of suit is not on table and not in hand
					else
					{
						// Play lowest “winning” ranked card of suit in hand
						if (lowestWinningOfSuit(table).getCardValue() != 0)
						{
							table.addCard(lowestWinningOfSuit(table), index);
							_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
							std::this_thread::sleep_for(std::chrono::seconds(3));
							return;
						}
						/*for (auto& c : _hand)
						{
							if (c.getSuit() == table.getLeadSuit() && c.getCardValue() > table.getTableHigh())
							{
								table.addCard(c, index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
						}*/
						// No cards in hand can beat winning card of lead suit, play lowest card of suit
						else
						{
							table.addCard(lowestOfSuit(table), index);
							_hand.erase(std::remove(_hand.begin(), _hand.end(), table.getTable()[index]), _hand.end());
							std::this_thread::sleep_for(std::chrono::seconds(3));
							return;
						}
						/*for (auto& c : _hand)
						{
							if (c.getSuit() == table.getLeadSuit())
							{
								table.addCard(c, index);
								_hand.erase(std::remove(_hand.begin(), _hand.end(), c), _hand.end());
								std::this_thread::sleep_for(std::chrono::seconds(3));
								return;
							}
						}*/
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
