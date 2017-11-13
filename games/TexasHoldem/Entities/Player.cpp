#include "Player.hpp"

Player::Player(int _id, const std::string& _nick)
	: id(_id), nickname(_nick), cash(1000), hand(Card(), Card()) {}

void Player::SetHand(Card _one, Card _two)
{
	hand.first = _one;
	hand.second = _two;
}

std::ostream& operator<<(std::ostream& os, const std::pair<Card, Card>& _hand)
{
	os << _hand.first << " " << _hand.second << std::endl;
	return os;
}
