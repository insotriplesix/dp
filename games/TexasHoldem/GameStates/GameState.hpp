#ifndef _GAME_STATE_HPP
#define _GAME_STATE_HPP

#include <functional>
#include <memory>
#include <vector>
#include <Windows.h>

#include "CLI.hpp"
#include "Game.hpp"

class GameState {
public:
	GameState(std::shared_ptr<Game> _game_data)
		: game_data(_game_data) {}

	virtual void Update() = 0;
	virtual void Render(std::shared_ptr<CLI> _ui) = 0;

protected:
	std::shared_ptr<Game> game_data;
};

#endif
