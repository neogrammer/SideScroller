#include <visual/AnimMgr.h>


AnimMgr::AnimMgr(const std::string& filename, std::function <std::variant<PlayerState, GoblinState>(GameEvent evt_)> onEvent_, AnimType type_)
	: animMap{}
	, mainState{ (type_ == AnimType::Player) ? std::variant<PlayerState, GoblinState>(PlayerState::Idle) : std::variant<PlayerState, GoblinState>(GoblinState::Idle) }
	, transientState{ (type_ == AnimType::Player) ? std::variant<PlayerState, GoblinState>(PlayerState::Idle) : std::variant<PlayerState, GoblinState>(GoblinState::Idle) }
	, currentAnimFrameTimeElapsed{ 0.f }
	, currentStateTimeElapsed{ 0.f }
	, onEvent{ onEvent_ }
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

void AnimMgr::changeAnimState(std::variant<PlayerState, GoblinState> newState_)
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
		
		
		if (animMap.animType == AnimType::Goblin)
		{
			if (std::get<GoblinState>(transientState) == GoblinState::Count)
			{
				transientState = mainState;
			}
			mainState = transientState;
			animMap.currAnim = Cfg::goblinStateStringLookup[std::pair(mainState, facingRight)];
		}
		else if (animMap.animType == AnimType::Player)
		{
			if (std::get<PlayerState>(transientState) == PlayerState::Count)
			{
				transientState = mainState;
			}
			mainState = transientState;
			animMap.currAnim = Cfg::playerStateStringLookup[std::pair(mainState, facingRight)];
		}
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

unsigned int AnimMgr::getCurrentIdx()
{
	return animMap.currentAnimation->getCurrentFrame();
}

sf::IntRect AnimMgr::getCurrentRect()
{
	return animMap.getRect();
}

void AnimMgr::loadAnimMap(std::string animFile_, AnimType type_)
{
	animMap.loadAnimMap(animFile_, type_);
}
