#ifndef PLAYER_H__
#define PLAYER_H__
#include <core/Cfg.h>
#include <visual/AnimMgr.h>
#include <functional>
#include <string>
#include <variant>

class Player
{
	std::function<std::variant<PlayerState>(GameEvent evt_)> Func;
	AnimMgr animMgr;

public:
	Player();
	~Player();
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player(Player&&) = delete;
	Player& operator=(Player&&) = delete;

	std::variant<PlayerState> onEvent(GameEvent evt_);

};

#endif