#include <visual/AnimMgr.h>


AnimMgr::AnimMgr(const std::string& filename, std::function <std::variant<PlayerState>(GameEvent evt_)> onEvent_, AnimType type_)
	: animMap{}
	, mainState{PlayerState::Idle}
	, transientState{ PlayerState::Idle }
	, currentAnimFrameTimeElapsed{ 0.f }
	, currentStateTimeElapsed{ 0.f }
	, onEvent{onEvent_}
{
	setup(filename, type_);
	animMap.currAnim = "idle";
}

AnimMgr::~AnimMgr()
{
}



void AnimMgr::setup(const std::string& filename, AnimType type_)
{
	loadAnimMap(filename, type_);
}

void AnimMgr::changeAnimState(std::variant<PlayerState> newState_)
{
	transientState = newState_;
}

void AnimMgr::update()
{

		animMap.currentAnimation = animMap.anims.at(mainState).get();
		animMap.currAnim = Cfg::stateStringLookup[mainState];

	animMap.currentAnimation->animate();

}

void AnimMgr::updateLate()
{
	mainState = transientState;
	
}

sf::IntRect AnimMgr::getCurrentRect()
{
	return animMap.getRect();
}

void AnimMgr::loadAnimMap(std::string animFile_, AnimType type_)
{
	animMap.loadAnimMap(animFile_, type_);
}
