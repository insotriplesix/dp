#ifndef _GAME_CONTROLLER_HPP
#define _GAME_CONTROLLER_HPP

#include "GameStateManager.hpp"

class GameController {
public:
	GameController(std::shared_ptr<Game> _game,
		std::shared_ptr<GameStateManager> _gsm,
		std::shared_ptr<CLI> _ui)
		: game(_game), gsm(_gsm), ui(_ui), game_over(false) {}

	bool IsGameOver()
	{
		auto players_left = game->GetPlayers().size();
		game_over = (players_left <= 1) ? true : false;

		return game_over;
	}

	void Render() { gsm->Render(ui); }
	void Update() { gsm->Update(); }

private:
	std::shared_ptr<Game> game;
	std::shared_ptr<GameStateManager> gsm;
	std::shared_ptr<CLI> ui;
	bool game_over;
};

#endif