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
	animMap.currAnim = "idleRt";
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
	animMap.currentAnimation->animate();
}

void AnimMgr::updateLate()
{
	

	if (mainState != transientState || changingDirection != "none")
	{
		if (changingDirection != "none")
		{
			if (changingDirection == "left")
			{
				facingRight = false;
			}
			else
			{
				facingRight = true;
			}
			changingDirection = "none";
		}
		animMap.currentAnimation->stop();
		mainState = transientState;
		animMap.currAnim = Cfg::playerStateStringLookup[std::pair(mainState, facingRight)];
		animMap.currentAnimation = animMap.anims.at(animMap.currAnim).get();
		animMap.currentAnimation->play();
		
	}
}

void AnimMgr::faceRight()
{
	if (facingRight == false)
		changingDirection = "right";
}

void AnimMgr::faceLeft()
{
	if (facingRight == true)
		changingDirection = "left";
}

sf::IntRect AnimMgr::getCurrentRect()
{
	return animMap.getRect();
}

void AnimMgr::loadAnimMap(std::string animFile_, AnimType type_)
{
	animMap.loadAnimMap(animFile_, type_);
}
