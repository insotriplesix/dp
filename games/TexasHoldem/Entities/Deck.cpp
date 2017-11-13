#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include "Deck.hpp"

Deck::Deck()
{
	for (int i = 0; i < Card::rank_t::R_LAST; ++i) {
		for (int j = 0; j < Card::suit_t::S_LAST; ++j) {
			cards.push_back(Card((Card::rank_t)i, (Card::suit_t)j));
		}
	}

	Shuffle();
}

Card Deck::DrawCard()
{
	if (!cards.empty()) {
		auto card = cards.back();
		cards.pop_back();
		return card;
	}
	else {
		return Card();
	}
}

void Deck::Shuffle()
{
	std::srand((unsigned)std::time(0));

	auto size = cards.size();
	int reps = 100;

	for (int k = 0; k < reps; ++k) {
		for (size_t i = 0; i < size - 1; ++i) {
			auto r = std::rand();
			auto j = i + r / (RAND_MAX / (size - i) + 1);
			std::iter_swap(cards.begin() + i, cards.begin() + j);
		}
	}
}
