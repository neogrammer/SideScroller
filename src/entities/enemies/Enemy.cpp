#include <entities/enemies/Enemy.h>


Enemy::Enemy(sf::Vector2f pos_, sf::Vector2f size_, Cfg::Textures texType_, sf::Vector2i texRectTilePos_, sf::Vector2i texRectSize_, sf::Vector2i texOffset_, sf::Vector2f vel_)
	: Scriptable{}
	, rec{pos_,size_,texType_,texRectTilePos_,texRectSize_,texOffset_,vel_}
	, currDir{ai::Direction::NotSet}
	, scriptMgr{}
	, facingRight{true}
{
}

Enemy::~Enemy()
{
}


