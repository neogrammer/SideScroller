#ifndef ANIMATION_H__
#define ANIMATION_H__
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <visual/AnimData.h>
class Animation
{
	std::vector<sf::IntRect> animRects{};
	AnimData data{};
	float animTimer{};

public:



	void LoadAnim(std::ifstream& animData);

	unsigned int getCurrentFrame();
	sf::IntRect getCurrentRect();

	const std::string& getName();
	Cfg::Textures getTexType();
	void play();
	void stop();
	void animate();





};

#endif