#ifndef ANIMMGR_H__
#define ANIMMGR_H__
#include <visual/AnimMap.h>
#include <string>
#include <variant>
#include <vector>
#include <functional>

class AnimMgr
{
	friend class Player;
	friend class Goblin;

	AnimMap animMap{};
	std::variant<PlayerState, GoblinState> mainState{};
	std::variant<PlayerState, GoblinState> transientState{};
	float currentStateTimeElapsed{};
	float currentAnimFrameTimeElapsed{};
    std::function <std::variant<PlayerState, GoblinState> (GameEvent evt_)> onEvent;
	bool facingRight{ true };
	std::string changingDirection{ "none"};
public:
	
	AnimMgr() = delete;
	AnimMgr(const std::string& filename, std::function <std::variant<PlayerState, GoblinState>(GameEvent evt_)> onEvent_, AnimType type_);
	~AnimMgr();
	AnimMgr(const AnimMgr&) = delete;
	AnimMgr(AnimMgr&&) = delete;
	AnimMgr& operator=(const AnimMgr&) = delete;
	AnimMgr& operator=(AnimMgr&&) = delete;
	void changeAnimState(std::variant<PlayerState, GoblinState> newState_);
	void setup(const std::string& filename, AnimType type_);
	void update();
	void updateLate();
	void faceRight();
	void faceLeft();
	unsigned int getCurrentIdx();
	sf::IntRect getCurrentRect();
	void loadAnimMap(std::string animFile_, AnimType type_);
};

#endif