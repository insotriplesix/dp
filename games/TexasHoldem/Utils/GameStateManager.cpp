#include "GameStateManager.hpp"

GameStateManager::GameStateManager(const std::vector<std::shared_ptr<GameState>>& _states)
	: game_states(_states)
{
	current_state = game_states[0];
	next_state = BLINDS;
}

void GameStateManager::SetCurrentState(state_t _state)
{
	if (_state > MENU && _state < S_COUNT) {
		current_state = game_states[_state];
		next_state = state_t(_state + 1);
	}
	else {
		current_state = game_states[1];
		next_state = PREFLOP;
	}
}