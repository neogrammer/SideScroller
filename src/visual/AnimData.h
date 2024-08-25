#ifndef ANIMDATA_H__
#define ANIMDATA_H__
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <core/Cfg.h>
enum class AnimLayoutType
{
	Block,
	Horizontal,
	Vertical,
	Count
};
struct AnimData
{


	std::string name{"Default"};
	unsigned int numFrames{1};
	sf::Vector2i frameSize{};
	Cfg::Textures textureSheetType{ Cfg::Textures::Count };
	sf::Vector2i texSheetStartFramePos{};
	unsigned int firstRowInnerOffset{}; // 0 if first frame is on top left of animation
	sf::Vector2i texSheetEndFramePos{};
	unsigned int texSheetPitch{1};
	unsigned int animPitch{1};
	bool firstFrameIsOffset{};
	AnimLayoutType layoutType{AnimLayoutType::Count};
	bool hasMultipleRows{};
	bool hasMultipleCols{};
	unsigned int numRowsBetween{};
	unsigned int colsInFirstRow{};
	unsigned int colsInLastRow{};
	float frameDelay{};
	float animStartDelay{};
	bool startDelayIsAlways{true};
	float animEndDelay{};
	bool endDelayIsAlways{ true };
	bool repeats{};
	int numRepeats{};
	bool playing{true};
	bool looping{true};
	bool stopped{};
	bool paused{};
	unsigned int frameIdx{};
};

#endif