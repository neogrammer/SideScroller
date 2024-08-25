#ifndef ANIMMAP_H__
#define ANIMMAP_H__
#include <visual/Animation.h>
#include <unordered_map>
#include <utility>
#include <memory>
class AnimMap
{
public:
	std::unordered_map<std::string, std::unique_ptr<Animation> > anims;

	AnimMap();
	~AnimMap();
	AnimMap(const AnimMap&) = delete;
	AnimMap(AnimMap&&) = delete;
	AnimMap& operator=(const AnimMap&) = delete;
	AnimMap& operator=(AnimMap&&) = delete;

	void loadAnimMap(const std::string& animSheet);
};

#endif