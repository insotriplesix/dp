#include "Card.hpp"

Card::Card(rank_t _rank, suit_t _suit) : rank(_rank), suit(_suit)
{
	setCardParameters();
}

void Card::setCardParameters()
{
	switch (rank)
	{
	case TWO:
		symbols.first = '2';
		value = 2;
		name += "Two";
		break;
	case THREE:
		symbols.first = '3';
		value = 3;
		name += "Three";
		break;
	case FOUR:
		symbols.first = '4';
		value = 4;
		name += "Four";
		break;
	case FIVE:
		symbols.first = '5';
		value = 5;
		name += "Five";
		break;
	case SIX:
		symbols.first = '6';
		value = 6;
		name += "Six";
		break;
	case SEVEN:
		symbols.first = '7';
		value = 7;
		name += "Seven";
		break;
	case EIGHT:
		symbols.first = '8';
		value = 8;
		name += "Eight";
		break;
	case NINE:
		symbols.first = '9';
		value = 9;
		name += "Nine";
		break;
	case TEN:
		symbols.first = 'T';
		value = 10;
		name += "Ten";
		break;
	case JACK:
		symbols.first = 'J';
		value = 11;
		name += "Jack";
		break;
	case QUEEN:
		symbols.first = 'Q';
		value = 12;
		name += "Queen";
		break;
	case KING:
		symbols.first = 'K';
		value = 13;
		name += "King";
		break;
	case ACE:
		symbols.first = 'A';
		value = 14;
		name += "Ace";
		break;
	case R_LAST:
	default:
		symbols.first = '?';
		value = 0;
		name += "???";
		break;
	}

	name += " of ";

	switch (suit)
	{
	case SPADES:
		symbols.second = 's';
		name += "Spades";
		break;
	case HEARTS:
		symbols.second = 'h';
		name += "Hearts";
		break;
	case CLUBS:
		symbols.second = 'c';
		name += "Clubs";
		break;
	case DIAMONDS:
		symbols.second = 'd';
		name += "Diamonds";
		break;
	case S_LAST:
	default:
		symbols.second = '?';
		name += "???";
		break;
	}
}

Card& Card::operator=(const Card& _card)
{
	rank = _card.rank;
	suit = _card.suit;
	symbols = _card.symbols;
	value = _card.value;
	name = _card.name;

	return *this;
}

std::ostream& operator<<(std::ostream& _os, const Card& _card)
{
	_os << "|" << _card.symbols.first << _card.symbols.second << "|";

	return _os;
}

std::ostream& operator<<(std::ostream& _os, const std::vector<Card>& _cards)
{
	for (auto& card : _cards) {
		_os << card;
	}

	return _os;
}
