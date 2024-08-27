#ifndef GAMESTATEMGR_H__
#define GAMESTATEMGR_H__
#include <string>

#include <memory>
#include <utility>
#include <stack>
#include <unordered_map>
#include <core/Cfg.h>
class Game;
class GameState;

class GameStateMgr
{
	GameStateType nextState{ GameStateType::None };
	bool needsToSwitchState{ false };
	bool popOffCurrent{ true };

	std::unordered_map<GameStateType, std::unique_ptr<GameState> > stateMap{};
public:
	std::stack<GameState*> stateStack;
	Game* game;
	GameStateMgr(Game* game_ = nullptr);
	void setGame(Game* game_);
	~GameStateMgr();
	GameStateMgr& operator=(const GameStateMgr&) = delete;
	GameStateMgr(const GameStateMgr&) = delete;
	GameStateMgr& operator=(GameStateMgr&&) = delete;
	GameStateMgr(GameStateMgr&&) = delete;

	void renderUnder();
	bool hasUnder();
	void input();
	void update();
	void updateLate();
	void render();
	void safeStateSwitch();
	void processEvent(sf::Event& e_);
	void changeState(GameStateType type_, bool popCurrent_ = true);
	void popTop();
	void resetState(GameStateType type_);

};

#endif