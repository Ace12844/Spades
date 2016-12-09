#include "Card.h"


Card::Card()
{
}

Card::Card(int rank, int suit)
{
	_rank = rank;
	_suit = suit;
}


Card::~Card()
{
}

void Card::print() const
{
	std::cout << _rank << _suit << " " ;
}

int Card::getSuit() const
{
	return _suit;
}

int Card::getRank() const
{
	return _rank;
}

int Card::getCardValue() const
{
	return _suit * 100 + _rank;
}

bool Card::operator<(const Card & c) const
{
	return (_suit * 100 + _rank < c._suit * 100 + c._rank);
}

bool Card::operator==(const Card & c) const
{
	return (_suit * 100 + _rank == c._suit * 100 + c._rank);
}

std::ostream & operator<<(std::ostream & out, const Card &card)
{
	std::string suit;
	std::string rank;
	switch (card.getRank())
	{
	case 1:
		rank = "2";
		break;
	case 2:
		rank = "3";
		break;
	case 3:
		rank = "4";
		break;
	case 4:
		rank = "5";
		break;
	case 5:
		rank = "6";
		break;
	case 6:
		rank = "7";
		break;
	case 7:
		rank = "8";
		break;
	case 8:
		rank = "9";
		break;
	case 9:
		rank = "10";
		break;
	case 10:
		rank = "J";
		break;
	case 11:
		rank = "Q";
		break;
	case 12:
		rank = "K";
		break;
	case 13:
		rank = "A";
		break;
	default:
		rank = "";
		break;
	}
	switch (card.getSuit())
	{
	case 1:
		suit = "C";
		break;
	case 2:
		suit = "D";
		break;
	case 3:
		suit = "H";
		break;
	case 4:
		suit = "S";
		break;
	default:
		suit = "";
		break;
	}
	out << rank << suit << " ";
	return out;
}
