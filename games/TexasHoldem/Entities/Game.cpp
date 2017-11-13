#include "Game.hpp"

Game::Game(int _number_of_players)
{
	pot = 0;
	deck = Deck();
	board_cards = std::vector<Card>();

	for (int id = 0; id < _number_of_players; ++id) {
		std::string nick = "player_" + std::to_string(id);
		players.push_back(Player(id, nick));
	}

	winners = std::vector<std::pair<Player, Combination>>();
}

void Game::DetermineWinner()
{
	auto combinations = std::vector<Combination>();
	std::vector<Card> pack;
	auto number_of_players = players.size();

	for (size_t i = 0; i < number_of_players; ++i) {
		pack = board_cards;
		pack.push_back(players[i].GetHand().first);
		pack.push_back(players[i].GetHand().second);

		auto combination_finder = CombinationFinder(pack);
		combinations.push_back(combination_finder.Start());
		combinations[i].player_id = i;

		pack.clear();
	}

	// sort by type
	std::sort(combinations.begin(), combinations.end(),
		[](const Combination& _comb1,
			const Combination& _comb2) -> bool
	{
		return _comb1.type > _comb2.type;
	});

	auto best_type = HIGH_CARD;
	int candidates_count = 0;

	for (const auto& combination : combinations) {
		if (combination.type >= best_type) {
			best_type = combination.type;
			++candidates_count;
		}
	}

	if (candidates_count == 1) {
		winners.push_back(std::make_pair(players[combinations[0].player_id], combinations[0]));
		players[combinations[0].player_id].IncreaseCash(pot);
	}
	else if (candidates_count > 1) {

		// compare by cards power
		int best_sum = 0;
		int winners_count = 0;
		auto id_sum = std::vector<std::pair<int, int>>();

		for (int i = 0; i < candidates_count; ++i) {
			int sum = 0;
			for (const auto& card : combinations[i].cards) {
				sum += card.GetValue();
			}

			id_sum.push_back(std::make_pair(i, sum));
		}

		std::sort(id_sum.begin(), id_sum.end(),
			[](const std::pair<int, int>& _item1,
				const std::pair<int, int>& _item2) -> bool
		{
			return _item1.second > _item2.second;
		});

		for (auto it = id_sum.begin(); it != id_sum.end(); ++it) {
			if (it->second == (it + 1)->second) {
				winners.push_back(std::make_pair(players[it->first], combinations[it->first]));
				++winners_count;
			}
			else {
				winners.push_back(std::make_pair(players[it->first], combinations[it->first]));
				++winners_count;
				break;
			}
		}

		if (winners_count == 1) {
			players[combinations[0].player_id].IncreaseCash(pot);
		}
		else if (winners_count > 1) {

			// Draw
			int regain = pot / winners_count;
			int modulo = pot % winners_count;

			for (int i = 0; i < winners_count; ++i) {
				if (i == 0) {
					players[combinations[i].player_id].IncreaseCash(regain + modulo);
				}
				else {
					players[combinations[i].player_id].IncreaseCash(regain);
				}
			}
		}
	}
}

void Game::Handout()
{
	for (auto& player : players) {
		auto card_one = deck.DrawCard();
		auto card_two = deck.DrawCard();
		player.SetHand(card_one, card_two);
	}
}

void Game::PlaceBlinds()
{
	auto default_value = 50;

	for (auto& player : players)
	{
		auto cash = player.GetCash();

		if (cash < default_value) {
			player.DecreaseCash(cash);
			IncreasePot(cash);
		}
		else {
			player.DecreaseCash(default_value);
			IncreasePot(default_value);
		}
	}
}

void Game::SetBoardCards(int count)
{
	for (int i = 0; i < count; ++i) {
		auto card = deck.DrawCard();
		board_cards.push_back(card);
	}
}

void Game::determinePlayersLeft()
{
	for (auto it = players.begin(); it != players.end();) {
		if (it->GetCash() <= 0) {
			it = players.erase(it);
		}
		else {
			++it;
		}
	}
}

void Game::Reset()
{
	pot = 0;
	deck = Deck();
	board_cards.clear();

	determinePlayersLeft();

	for (auto& player : players) {
		player.SetHand(Card(), Card());
	}
	
	winners.clear();
}
