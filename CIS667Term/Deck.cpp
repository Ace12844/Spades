#include "Deck.h"
//#define TEST_DECK
Deck::Deck()
{
	// Create a deck of cards
	for (int suit = 1; suit <= 4; suit++)
	{
		for (int rank = 1; rank <= 13; rank++)
		{
			deckOfCards.push_back(Card(rank, suit));
		} /* end for rank */
	} /* end for suit */
}


Deck::~Deck()
{
}

void Deck::printDeck()
{
	for (int x = 0; x < deckOfCards.size(); x++)
	{
		std::cout << deckOfCards[x] << " ";
	}
	std::cout << std::endl;
}

void Deck::shuffle()
{
	std::random_shuffle(deckOfCards.begin(), deckOfCards.end());
}

void Deck::dealCards(std::vector<Card>& hand1, std::vector<Card>& hand2, std::vector<Card>& hand3, std::vector<Card>& hand4)
{
	for (int x = 0; x < deckOfCards.size(); x++)
	{
		if(x % 4 == 0)
			hand1.push_back(deckOfCards[x]);
		else if (x % 4 == 1)
			hand2.push_back(deckOfCards[x]);
		else if (x % 4 == 2)
			hand3.push_back(deckOfCards[x]);
		else
			hand4.push_back(deckOfCards[x]);
	}
}

#ifdef TEST_DECK
void main()
{
	// Create Deck object
	Deck cards;
	
	// Shuffle Deck
	cards.shuffle();

	// PRINT DECK FUNCTION TEST
	// Print Deck after shuffle
	std::cout << "PRINT DECK AFTER SHUFFLE" << std::endl;
	cards.printDeck();

	// DEAL CARDS FUNCTION TEST
	// Create four vectors of cards to hold hands
	std::vector<Card> player1;
	std::vector<Card> player2;
	std::vector<Card> player3;
	std::vector<Card> player4;

	// Deal cards to player hands
	cards.dealCards(player1, player2, player3, player4);

	std::cout << "PRINT PLAYER ONE HAND" << std::endl;
	// Print each hand
	for (auto& c : player1)
	{
		std::cout << c;
	}
	std::cout << std::endl;

	std::cout << "PRINT PLAYER TWO HAND" << std::endl;
	// Print each hand
	for (auto& c : player2)
	{
		std::cout << c;
	}
	std::cout << std::endl;

	std::cout << "PRINT PLAYER THREE HAND" << std::endl;
	// Print each hand
	for (auto& c : player3)
	{
		std::cout << c;
	}
	std::cout << std::endl;

	std::cout << "PRINT PLAYER FOUR HAND" << std::endl;
	// Print each hand
	for (auto& c : player4)
	{
		std::cout << c;
	}
	std::cout << std::endl;


}
#endif // TEST_DECK
