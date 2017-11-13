#ifndef _DECK_HPP
#define _DECK_HPP

#include <vector>
#include "Card.hpp"

class Deck {
public:
	Deck();

	const int GetSize() const { return cards.size(); }
	const std::vector<Card>& GetCards() const { return cards; }

	Card DrawCard();
	void Shuffle();

private:
	std::vector<Card> cards;
};

#endif
