#ifndef HUD_H__
#define HUD_H__
#include <SFML/Graphics/Texture.hpp>
class Player;
class HUD
{
public:
	sf::Texture* lifeBarTex;

	void setLifeBarTex(sf::Texture& tex_);
	void drawLifeBar(Player& player_);
	void render(Player& player_);
};

#endif