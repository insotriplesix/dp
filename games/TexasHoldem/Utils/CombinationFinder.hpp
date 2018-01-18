#ifndef _COMBINATION_FINDER_HPP
#define _COMBINATION_FINDER_HPP

#include <algorithm>
#include <memory>
#include "Card.hpp"

enum comb_type_t {
	HIGH_CARD, ONE_PAIR, TWO_PAIR, TRIPS,
	STRAIGHT, FLUSH, FULL_HOUSE, QUADS,
	STRAIGHT_FLUSH
};

struct Combination {
	int player_id;
	std::vector<Card> cards;
	enum comb_type_t type;
};

class CombinationFinder {
public:
	Combination combination;

	CombinationFinder::CombinationFinder(std::vector<Card> _pack)
		: pack(_pack)
	{
		combination = Combination();
	}

	Combination Start();

private:
	std::vector<Card> pack;

	bool searchStraightFlush();
	bool searchQuads();
	bool searchFullHouse();
	bool searchFlush();
	bool searchStraight();
	bool searchTrips();
	bool searchTwoPair();
	bool searchOnePair();
	bool searchHighCard();
};

#endif
