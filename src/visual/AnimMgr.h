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
	AnimMap anims{};
	std::variant<PlayerState> mainState{};
	std::variant<PlayerState> transientState{};
	float currentStateTimeElapsed{};
	float currentAnimFrameTimeElapsed{};
	std::function <std::variant<PlayerState>(GameEvent evt_)> onEvent;
public:
	AnimMgr() = delete;
	AnimMgr(const std::string& filename, std::function <std::variant<PlayerState>(GameEvent evt_)> onEvent_);
	~AnimMgr();
	AnimMgr(const AnimMgr&) = delete;
	AnimMgr(AnimMgr&&) = delete;
	AnimMgr& operator=(const AnimMgr&) = delete;
	AnimMgr& operator=(AnimMgr&&) = delete;
	void setup(const std::string& filename);
	//std::variant<PlayerState> onEvent(); // does checks using the transient state, other objects only see the main state and main is changed at end of frame
	void update();
	void updateLate();
};

#endif