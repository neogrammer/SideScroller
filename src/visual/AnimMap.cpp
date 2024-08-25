#include "AnimMap.h"
#include <fstream>

AnimMap::AnimMap()
	: anims{}
	, currentAnimation{ nullptr }
{
}

AnimMap::~AnimMap()
{
}

sf::IntRect AnimMap::getRect()
{
	sf::IntRect tmp = { currentAnimation->getCurrentRect() };
	return tmp;
}

void AnimMap::loadAnimMap(const std::string& animSheet, AnimType animType_)
{
	animType = animType_;
	anims.clear();
	std::ifstream file;
	file.open(animSheet);
	bool first = true;
	if (file.is_open() && file.good())
	{ 
		int numAnims;
		file >> numAnims;

		for (int i = 0; i < numAnims; i++)
		{
			std::unique_ptr anim = std::make_unique<Animation>();
			anim->LoadAnim(file);
			// anim->LoadAnim(file, common data points for an AnimMap) to shorten the animmap file
			anim->data.animType = animType_;
			
			anims.emplace(std::pair{ Cfg::animStateLookup[std::pair(animType_, anim->data.name)],std::move(anim) });
			if (first)
			{
				first = false;
				currentAnimation = anims.at(PlayerState::Idle).get();
			}
		}
	}
	else
	{
		throw std::runtime_error("anim map file read error: " + animSheet);
	}
}
