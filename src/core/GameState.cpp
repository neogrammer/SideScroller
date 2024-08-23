#include <core/GameState.h>

GameState::GameState(GameStateMgr* owner_)
	: paused{false}
	, owner{owner_}
{
}

GameState::~GameState()
{
	owner = nullptr;
}
