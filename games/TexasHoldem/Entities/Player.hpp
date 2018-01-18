#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <string>
#include "Card.hpp"

class Player {
public:
	Player(int _id, const std::string& _nick);

	int GetID() const { return id; }
	std::string GetNickName() const { return nickname; }
	int GetCash() const { return cash; }
	std::pair<Card, Card> GetHand() const { return hand; }

	void SetHand(Card, Card);
	void SetCash(int _cash) { cash = _cash; }
	void IncreaseCash(int _amount) { cash += _amount; }
	void DecreaseCash(int _amount) { cash -= _amount; }

	friend std::ostream& operator<<(std::ostream&, const std::pair<Card, Card>&);

private:
	int id;
	std::string nickname;
	int cash;
	std::pair<Card, Card> hand;
};

#endif
