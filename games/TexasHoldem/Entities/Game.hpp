#ifndef _GAME_HPP
#define _GAME_HPP

#include "CombinationFinder.hpp"
#include "Deck.hpp"
#include "Player.hpp"

class Game {
public:
	Game::Game() : Game(2) {}
	Game(int _number_of_players);

	int GetPot() const { return pot; }
	Deck GetDeck() const { return deck; }
	const std::vector<Card>& GetBoardCards() const { return board_cards; }
	const std::vector<Player>& GetPlayers() const { return players; }
	const std::vector<std::pair<Player, Combination>>& GetWinners() const { return winners; }

	void DetermineWinner();
	void Handout();
	void IncreasePot(int _amount) { pot += _amount; }
	void PlaceBet(int _id, int _bet)
	{
		players[_id].DecreaseCash(_bet);
		IncreasePot(_bet);
	}
	void PlaceBlinds();
	void Reset();
	void SetBoardCards(int);

private:
	int pot;
	Deck deck;
	std::vector<Card> board_cards;
	std::vector<Player> players;
	std::vector<std::pair<Player, Combination>> winners;

	void determinePlayersLeft();
};

#endif
