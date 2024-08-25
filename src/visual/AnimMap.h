#ifndef ANIMMAP_H__
#define ANIMMAP_H__
#include <visual/Animation.h>
#include <unordered_map>
#include <utility>
#include <memory>
#include <variant>
class AnimMap
{
public:
	std::unordered_map<std::variant<PlayerState>, std::unique_ptr<Animation> > anims;
	Animation* currentAnimation{ nullptr };

	AnimMap();
	~AnimMap();
	AnimMap(const AnimMap&) = delete;
	AnimMap(AnimMap&&) = delete;
	AnimMap& operator=(const AnimMap&) = delete;
	AnimMap& operator=(AnimMap&&) = delete;

	std::string currAnim{"idle"};
	AnimType animType{ AnimType::Count };

	sf::IntRect getRect();
	void loadAnimMap(const std::string& animSheet, AnimType animType_);
};

#endif