#include "HUD.h"
#include <core/globals.h>
#include <entities/player/player.h>
void HUD::setLifeBarTex(sf::Texture& tex_)
{
	lifeBarTex = &tex_;
		
}

void HUD::drawLifeBar(Player& player_)
{
	sf::Sprite lifeBarFull = {};
	lifeBarFull.setTexture(*lifeBarTex);
	lifeBarFull.setPosition(30.f, 40.f);
	lifeBarFull.setTextureRect({ {0, 0},{ 402, 61} });

	float fullWidth = ((float)player_.getHealth() / (float)player_.getMaxHealth());
	lifeBarFull.setScale(fullWidth, 1.f);

	float emptyPosX = 30.f + fullWidth * lifeBarFull.getTextureRect().width;


	sf::Sprite lifeBarEmpty = {};
	lifeBarEmpty.setTexture(*lifeBarTex);
	lifeBarEmpty.setPosition(emptyPosX, 40.f);
	lifeBarEmpty.setTextureRect({ {0, 61},{ 402, 61} });
	float emptyWidth = lifeBarFull.getPosition().x + lifeBarEmpty.getTextureRect().width - emptyPosX;

	lifeBarEmpty.setScale(emptyWidth / lifeBarEmpty.getTexture()->getSize().x, 1.f);

	gWnd.draw(lifeBarFull);
	gWnd.draw(lifeBarEmpty);

}

void HUD::render(Player& player_)
{
	gWnd.setView(gWnd.getDefaultView());

	drawLifeBar(player_);

}
