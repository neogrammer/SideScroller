#include "AnimMap.h"
#include <fstream>

AnimMap::AnimMap()
	: anims{}
{
}

AnimMap::~AnimMap()
{
}

void AnimMap::loadAnimMap(const std::string& animSheet)
{
	anims.clear();
	std::ifstream file;
	file.open(animSheet);

	if (file.is_open() && file.good())
	{ 
		int numAnims;
		file >> numAnims;

		for (int i = 0; i < numAnims; i++)
		{
			std::unique_ptr anim = std::make_unique<Animation>();
			anim->LoadAnim(file);
			// anim->LoadAnim(file, common data points for an AnimMap) to shorten the animmap file
			anims.emplace(std::pair{ anim->getName(),std::move(anim) });
		}
	}
	else
	{
		throw std::runtime_error("anim map file read error: " + animSheet);

	}
}
