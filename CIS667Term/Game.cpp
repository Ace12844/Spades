#include "Game.h"
#include <ctime>
#include <stdlib.h>

Game::~Game()
{
}

void Game::playGame()
{
	/*do
	{*/
		// Reset available cards
		table.resetAvailableCard();
		// Clear flags
		table.resetLeadWithSpade();
		// Clear Table before start of round
		table.clearTable();
		// Shuffle Deck
		srand(time(0));
		deck.shuffle();
		// Deal hands : Number of hands played determines who the dealer is
		// 1 : comp1,comp2,comp3,user
		// 2 : comp2,comp3,user,comp1
		// 3 : comp3,user,comp1,comp2
		// 4 : user,comp1,comp2,comp3
		dealCards(handCount % 4);		// (Hand count % 4) + 1 determines the dealer (1: User, 2: Comp1, 3: Comp2, 4: Comp3). Always in range 1 - 4
										// Players bid : Number of hands determines who the dealer is and betting starts with the player after dealer user->comp1->comp2->comp3->user->etc...

		displayHands();
		bid(handCount % 4);
		// Start first round based on dealer
		// SPECIAL CASE: For the first round, the player after dealer plays first. Should player 3 be the dealer the user must play first
		if (handCount % 4 == 3)			//dealer is computer player 3
			play(0);					// User plays first 
		// Otherwise play must go to next player based on hand count
		else							// Dealer is either the user, computer player 1 or computer player 3
			play((handCount % 4) + 1);	// Get hand cound which by elimination in first if statement must be 0-2 inclusive. Make the next player start play

		table.displayWinner();
		winner = table.getWinner();
		awardTrick(winner);
		do
		{
			// Space next play out
			std::cout << std::endl << std::endl;
			// Clear Table
			table.clearTable();
			// Play hand according to winner
			displayHands();
			play(winner);
			table.displayWinner();
			winner = table.getWinner();
			awardTrick(winner);
			table.clearPlayedCards();
		} while ((user.getHand().size() + comp1.getHand().size() + comp2.getHand().size() + comp3.getHand().size()) > 0);	// continue to loop until all cards have been removed from the players hands
																															// Do scoring
	//	if ((user.getTricks() + comp2.getTricks()) >= (user.getBid() + comp2.getBid()) ? teamOneScore += (user.getBid() + comp2.getBid()) * 10 : teamOneScore -= (user.getBid() + comp2.getBid()) * 10);
	//	if ((comp1.getTricks() + comp3.getTricks()) >= (comp1.getBid() + comp3.getBid()) ? teamTwoScore += (comp1.getBid() + comp3.getBid()) * 10 : teamTwoScore -= (comp1.getBid() + comp3.getBid()) * 10);
	//	// Increment handCount 
	//	handCount++;
	//} while (teamOneScore < 100 || teamTwoScore < 100);
}


void Game::dealCards(int dealer)
{
	switch (dealer)
	{
	case 0:
		deck.dealCards(comp1.getHand(), comp2.getHand(), comp3.getHand(), user.getHand());
		sortHands();
		break;
	case 1:
		deck.dealCards(comp2.getHand(), comp3.getHand(), user.getHand(), comp1.getHand());
		sortHands();
		break;
	case 2:
		deck.dealCards(comp3.getHand(), user.getHand(), comp1.getHand(), comp2.getHand());
		sortHands();
		break;
	case 3:
		deck.dealCards(user.getHand(), comp1.getHand(), comp2.getHand(), comp3.getHand());
		sortHands();
		break;
	default:
		break;
	}
}

void Game::bid(int dealer)
{
	switch (dealer)
	{
	case 0:
		comp1.makeBid();
		comp2.makeBid();
		comp3.makeBid();
		user.makeBid();
		break;
	case 1:
		comp2.makeBid();
		comp3.makeBid();
		user.makeBid();
		comp1.makeBid();
		break;
	case 2:
		comp3.makeBid();
		user.makeBid();
		comp1.makeBid();
		comp2.makeBid();
		break;
	case 3:
		user.makeBid();
		comp1.makeBid();
		comp2.makeBid();
		comp3.makeBid();
		break;
	default:
		break;
	}
}

void Game::play(int winner)
{
	switch (winner)
	{
	case 0:
		table.display();
		user.play(table, 0);
		comp1.play(table, 1);
		comp2.play(table, 2);
		comp3.play(table, 3);
		table.display();
		std::this_thread::sleep_for(std::chrono::seconds(3));
		break;
	case 1:
		comp1.play(table, 1);
		comp2.play(table, 2);
		comp3.play(table, 3);
		table.display();
		std::cout << std::endl;
		user.play(table, 0);
		table.display();
		std::this_thread::sleep_for(std::chrono::seconds(3));
		break;
	case 2:
		comp2.play(table, 2);
		comp3.play(table, 3);
		table.display();
		std::cout << std::endl;
		user.play(table, 0);
		comp1.play(table, 1);
		table.display();
		std::this_thread::sleep_for(std::chrono::seconds(3));
		break;
	case 3:
		comp3.play(table, 3);
		table.display();
		std::cout << std::endl;
		user.play(table, 0);
		table.display();
		std::cout << std::endl;
		comp1.play(table, 1);
		comp2.play(table, 2);
		table.display();
		std::this_thread::sleep_for(std::chrono::seconds(3));
		break;
	default:
		break;
	}
}

void Game::awardTrick(int winner)
{
	switch (winner)
	{
	case 0:
		user.giveTrick();
		break;
	case 1:
		comp1.giveTrick();
		break;
	case 2:
		comp2.giveTrick();
		break;
	case 3:
		comp3.giveTrick();
		break;
	default:
		break;
	}
}

void Game::sortHands()
{
	std::sort(user.getHand().begin(), user.getHand().end());
	std::sort(comp1.getHand().begin(), comp1.getHand().end());
	std::sort(comp2.getHand().begin(), comp2.getHand().end());
	std::sort(comp3.getHand().begin(), comp3.getHand().end());
}

void Game::displayHands()
{
	std::cout << "Player 1 Hand: ";
	user.displayHand();
	std::cout << "Player 2 Hand: ";
	comp1.displayHand();
	std::cout << "Player 3 Hand: ";
	comp2.displayHand();
	std::cout << "Player 4 Hand: ";
	comp3.displayHand();
}
