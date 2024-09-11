#ifndef HUD_H__
#define HUD_H__
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
class Player;
class HUD
{
public:
	sf::Texture* lifeBarTex{ nullptr };
	//player data
	int pHealth;
	int pHealthMax;
	sf::RectangleShape redShape{};
	
	void setUpShape();

	void setLifeBarTex(sf::Texture& tex_);
	void drawLifeBar(Player& player_);
	void render(Player& player_);
};

#endif