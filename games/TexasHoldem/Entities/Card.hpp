#ifndef _CARD_HPP
#define _CARD_HPP

#include <iostream>
#include <string>
#include <vector>

class Card {
public:
	enum rank_t {
		TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
		NINE, TEN, JACK, QUEEN, KING, ACE, R_LAST
	};
	enum suit_t { SPADES, HEARTS, CLUBS, DIAMONDS, S_LAST };

	Card::Card() : Card(R_LAST, S_LAST) {}
	Card(rank_t, suit_t);

	rank_t Card::GetRank() const { return rank; }
	suit_t Card::GetSuit() const { return suit; }
	std::pair<char, char> GetSymbols() const { return symbols; }
	int GetValue() const { return value; }
	std::string GetName() const { return name; }

	Card& operator=(const Card&);
	friend std::ostream& operator<<(std::ostream&, const Card&);
	friend std::ostream& operator<<(std::ostream&, const std::vector<Card>&);

private:
	rank_t rank;
	suit_t suit;
	std::pair<char, char> symbols;
	int value;
	std::string name;

	void setCardParameters();
};

#endif
