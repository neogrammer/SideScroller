#ifndef ANIMATION_H__
#define ANIMATION_H__
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <visual/AnimData.h>
#include <variant>
#include <utility>

class Animation
{
	friend class AnimMap;
	std::vector<sf::IntRect> animRects{};
	AnimData data{};
	float animTimer{};

public:



	void LoadAnim(std::ifstream& animData);

	unsigned int getCurrentFrame();
	sf::IntRect getCurrentRect();

	std::variant<PlayerState> getName();
	Cfg::Textures getTexType();
	void play();
	void stop();
	void animate();





};

#endif