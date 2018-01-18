#include "GameController.hpp"

#include "Menu.hpp"
#include "Blinds.hpp"
#include "Preflop.hpp"
#include "Flop.hpp"
#include "Turn.hpp"
#include "River.hpp"
#include "EndRound.hpp"

std::vector<std::shared_ptr<GameState>> InitStates(std::shared_ptr<Game>);

int main()
{
	while (1) {
		auto game = std::make_shared<Game>();
		auto states = InitStates(game);
		auto gsm = std::make_shared<GameStateManager>(states);
		auto cli = std::make_shared<CLI>();
		auto gc = std::make_shared<GameController>(game, gsm, cli);

		do {
			gc->Render();
			gc->Update();
		} while (!gc->IsGameOver());
	}

	return 0;
}

std::vector<std::shared_ptr<GameState>> InitStates(std::shared_ptr<Game> _game)
{
	auto states = std::vector<std::shared_ptr<GameState>>();

	states.push_back(std::make_shared<Menu>(_game));
	states.push_back(std::make_shared<Blinds>(_game));
	states.push_back(std::make_shared<Preflop>(_game));
	states.push_back(std::make_shared<Flop>(_game));
	states.push_back(std::make_shared<Turn>(_game));
	states.push_back(std::make_shared<River>(_game));
	states.push_back(std::make_shared<EndRound>(_game));

	return states;
}