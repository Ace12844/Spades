#include "Table.h"
//#define TEST_TABLE
Table::Table() : table(4,Card(0,0))
{
	_leadSuit = 0;
	topCardIdx = -1;
	tableHigh = 0;
	leadWithSpade = false;
}


Table::~Table()
{
}

void Table::addCard(Card card, int idx)
{
	// if this is the first card (lead suit has not been set) then sent lead suit to card played
	if (_leadSuit == 0)
		_leadSuit = card.getSuit();
	// If the card follows the suit add to table
	// If the card is a spades which signals a player has cut and card is automatically added to table
	// NOTE: Lead suit can be spades which still satisfies first comparison statement
	if (card.getSuit() == _leadSuit || card.getSuit() == 4)
	{
		// Add card to corresponding players place on table
		// card.getSuit() * 100 + card.getRank() gives card a numerical value for comparison ex. 300 + 12 would be the King of Hearts
		table[idx] = card;
		if (card.getCardValue() > tableHigh)
		{
			topCardIdx = idx;
			tableHigh = card.getSuit() * 100 + card.getRank();
		}	
	}
	// This would mean that a player has played off suit and card value holds no weight so update to topCardIndex and tableHigh are unnecessary
	else
		table[idx] = card;
}

int Table::getWinner()
{
	return topCardIdx;
}

void Table::clearTable()
{
	
	for (int x = 0; x < 4; x++)
		table[x] = Card(0,0);
	_leadSuit = 0;
	topCardIdx = -1;
	tableHigh = 0;
}

void Table::display()
{
	for (int x = 0; x < 4; x++)
		std::cout << "Player " << x+1 << " card: " << table[x] << std::endl;
}

int Table::getLeadSuit()
{
	return _leadSuit;
}

std::vector<Card> Table::getTable()
{
	return table;
}

void Table::allowCut()
{
	leadWithSpade = true;
}

void Table::resetLeadWithSpade()
{
	leadWithSpade = false;
}

bool Table::canLeadWithSpade()
{
	return leadWithSpade;
}

std::map<int, std::vector<Card>> Table::getRemainingCards()
{
	return remainingCards;
}

int Table::getTableHigh()
{
	return tableHigh;
}

void Table::resetAvailableCard()
{
	for (int suit = 1; suit <= 4; suit++)
	{
		for (int rank = 13; rank >= 1; rank--)
		{
			remainingCards[suit].push_back(Card(rank, suit));
		} /* end for rank */
	}
}

void Table::clearPlayedCards()
{
	for (auto& c : table)
	{
		remainingCards[c.getSuit()].erase(std::remove(remainingCards[c.getSuit()].begin(), remainingCards[c.getSuit()].end(), c), remainingCards[c.getSuit()].end());
	}
}

void Table::displayWinner()
{
	if (topCardIdx == 0)
		std::cout << "You won the trick!" << std::endl;
	else
		std::cout << "Player " << topCardIdx + 1 << " won the trick!" << std::endl << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

#ifdef TEST_TABLE
void main()
{
	// CREATE TABLE
	Table table;

	// DISPLAY EMPTY TABLE
	table.display();
	std::cout << std::endl;

	// ADD PLAYER ONE CARD
	Card card1(7, 3);
	table.addCard(card1, 0);

	// DISPLAY TABLE
	table.display();
	std::cout << std::endl;

	// CHECK HIGHEST CARD
	std::cout << "Player: " << table.getWinner() + 1 << " has the highest card" << std::endl;

	// ADD PLAYER TWO CARD
	Card card2(10, 2);
	table.addCard(card2, 1);

	// DISPLAY TABLE
	table.display();
	std::cout << std::endl;

	// CHECK HIGHEST CARD
	std::cout << "Player: " << table.getWinner() + 1 << " has the highest card" << std::endl;

	// ADD PLAYER THREE CARD
	Card card3(13, 3);
	table.addCard(card3, 2);

	// DISPLAY TABLE
	table.display();
	std::cout << std::endl;

	// CHECK HIGHEST CARD
	std::cout << "Player: " << table.getWinner() + 1 << " has the highest card" << std::endl;

	// ADD PLAYER FOUR CARD
	Card card4(13, 4);
	table.addCard(card4, 3);
	// DISPLAY TABLE
	table.display();
	std::cout << std::endl;

	// CHECK HIGHEST CARD
	std::cout << "Player: " << table.getWinner() + 1 << " has the highest card" << std::endl;

	// RESET TABLE AND PRINT
	table.clearTable();
	table.display();
	std::cout << std::endl;
}
#endif // TEST_TABLE

