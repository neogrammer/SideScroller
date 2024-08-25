#include <visual/AnimMgr.h>


AnimMgr::AnimMgr(const std::string& filename, std::function <std::variant<PlayerState>(GameEvent evt_)> onEvent_)
	: anims{}
	, mainState{PlayerState::Idle}
	, transientState{ PlayerState::Idle }
	, currentAnimFrameTimeElapsed{ 0.f }
	, currentStateTimeElapsed{ 0.f }
	, onEvent{onEvent_}
{
	setup(filename);
}

AnimMgr::~AnimMgr()
{
}

void AnimMgr::setup(const std::string& filename)
{
	anims.loadAnimMap(filename);
}



void AnimMgr::update()
{

}

void AnimMgr::updateLate()
{
	mainState = transientState;
}
