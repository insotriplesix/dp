#include "CombinationFinder.hpp"

typedef bool(CombinationFinder::*solve_function)();

Combination CombinationFinder::Start()
{
	solve_function solve_ptr[9] = { &CombinationFinder::searchStraightFlush,
		&CombinationFinder::searchQuads, &CombinationFinder::searchFullHouse,
		&CombinationFinder::searchFlush, &CombinationFinder::searchStraight,
		&CombinationFinder::searchTrips, &CombinationFinder::searchTwoPair,
		&CombinationFinder::searchOnePair, &CombinationFinder::searchHighCard
	};
	
	std::sort(pack.begin(), pack.end(),
		[](const Card& _card1, const Card& _card2) -> bool
	{
		return _card1.GetRank() > _card2.GetRank();
	});

	for (int i = HIGH_CARD; i <= STRAIGHT_FLUSH; ++i) {
		if ((this->*solve_ptr[i])() && combination.cards.size() == 5
			|| combination.cards.size() == 5) {
			return Combination(combination);
		}
	}

	return Combination();
}

bool CombinationFinder::searchStraightFlush()
{
	if (searchFlush()) {
		pack.clear();
		pack = combination.cards;

		if (searchStraight()) {
			combination.type = STRAIGHT_FLUSH;
			return true;
		}
	}

	std::sort(pack.begin(), pack.end(),
		[](const Card& _card1, const Card& _card2) -> bool
	{
		return _card1.GetRank() > _card2.GetRank();
	});

	return false;
}

bool CombinationFinder::searchQuads()
{
	auto size = pack.size();

	for (size_t i = 0; i < size - 3; ++i) {
		if (pack[i].GetRank() == pack[i + 1].GetRank() &&
			pack[i].GetRank() == pack[i + 2].GetRank() &&
			pack[i].GetRank() == pack[i + 3].GetRank())
		{
			combination.cards.push_back(pack[i]);
			combination.cards.push_back(pack[i + 1]);
			combination.cards.push_back(pack[i + 2]);
			combination.cards.push_back(pack[i + 3]);

			combination.type = combination.type > QUADS ?
				combination.type : QUADS;

			pack.erase(pack.begin() + i, pack.begin() + i + 4);

			searchHighCard();

			return true;
		}
	}

	return false;
}

bool CombinationFinder::searchFullHouse()
{
	if (searchTrips() && searchOnePair()) {
		combination.type = combination.type > FULL_HOUSE ?
			combination.type : FULL_HOUSE;
		return true;
	}

	return false;
}

bool CombinationFinder::searchFlush()
{
	std::vector<Card> temp = pack;

	std::sort(temp.begin(), temp.end(),
		[](const Card& _card1, const Card& _card2) -> bool
	{
		return _card1.GetSuit() > _card2.GetSuit();
	});

	auto size = temp.size();

	for (int i = Card::SPADES; i <= Card::DIAMONDS; ++i) {
		for (size_t j = 0; j < size - 4; ++j) {
			if (temp[j].GetSuit() == i && temp[j + 4].GetSuit() == i)
			{
				combination.cards.insert(combination.cards.end(),
					temp.begin() + j, temp.begin() + j + 4);

				combination.type = combination.type > FLUSH ?
					combination.type : FLUSH;

				return true;
			}
		}
	}

	return false;
}

bool CombinationFinder::searchStraight()
{
	std::sort(pack.begin(), pack.end(),
		[](const Card& _card1, const Card& _card2) -> bool
	{
		return _card1.GetRank() > _card2.GetRank();
	});

	auto size = pack.size();

	for (size_t i = 0; i < size - 4; ++i) {
		auto a = (pack[i].GetRank() + pack[i + 4].GetRank()) / 2;
		auto b = (pack[i + 1].GetRank() + pack[i + 3].GetRank()) / 2;

		if ((a == b == pack[i + 2].GetRank())) {
			combination.type = combination.type > STRAIGHT ?
				combination.type : STRAIGHT;
			return true;
		}
	}

	return false;
}

bool CombinationFinder::searchTrips()
{
	auto size = pack.size();

	for (size_t i = 0; i < size - 2; ++i) {
		if (pack[i].GetRank() == pack[i + 1].GetRank() &&
			pack[i].GetRank() == pack[i + 2].GetRank())
		{
			combination.cards.push_back(pack[i]);
			combination.cards.push_back(pack[i + 1]);
			combination.cards.push_back(pack[i + 2]);

			combination.type = combination.type > TRIPS ?
				combination.type : TRIPS;

			pack.erase(pack.begin() + i, pack.begin() + i + 3);

			return true;
		}
	}

	return false;
}

bool CombinationFinder::searchTwoPair()
{
	if (searchOnePair() && searchOnePair()) {
		combination.type = combination.type > TWO_PAIR ?
			combination.type : TWO_PAIR;
		return true;
	}

	return false;
}

bool CombinationFinder::searchOnePair()
{
	auto size = pack.size();

	for (size_t i = 0; i < size - 1; ++i) {
		if (pack[i].GetRank() == pack[i + 1].GetRank()) {
			combination.cards.push_back(pack[i]);
			combination.cards.push_back(pack[i + 1]);

			combination.type = combination.type > ONE_PAIR ?
				combination.type : ONE_PAIR;

			pack.erase(pack.begin() + i, pack.begin() + i + 2);

			return true;
		}
	}

	return false;
}

bool CombinationFinder::searchHighCard()
{
	pack.pop_back();
	pack.pop_back();

	combination.cards.insert(combination.cards.end(), pack.begin(), pack.end());

	combination.type = combination.type > HIGH_CARD ?
		combination.type : HIGH_CARD;

	return true;
}
