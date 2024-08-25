#include <core/rec.h>
#include <core/globals.h>
rec::rec()
	: pos{ 0.f,0.f }
	, prevPos{0.f,0.f}
	, size{ 0.f,0.f }
	, texType{ Cfg::Textures::Count }
	, texRectPos{ 0,0 }
	, texPosOffset{ 0,0 }
	, texRectSize{ 0,0 }
	, vel{ 0.f,0.f }
{}

rec::rec(sf::Vector2f pos_, sf::Vector2f size_, Cfg::Textures texType_, sf::Vector2i texRectTilePos_, sf::Vector2i texRectSize_, sf::Vector2i texOffset_, sf::Vector2f vel_)
{
	pos = pos_;
	prevPos = pos_;
	size = size_;
	texType = texType_;
	texRectPos = { (texRectTilePos_.x * texRectSize_.x), (texRectTilePos_.y * texRectSize_.y) };
	texPosOffset = texOffset_;
	texRectSize = texRectSize_;

	vel = vel_;
}

void rec::set(sf::Vector2f pos_, sf::Vector2f size_, Cfg::Textures texType_, sf::Vector2i texRectTilePos_, sf::Vector2i texRectSize_, sf::Vector2i texOffset_ , sf::Vector2f vel_ )
{
	pos = pos_;
	prevPos = pos_;
	size = size_;
	texType = texType_;
	texRectPos = { (texRectTilePos_.x * texRectSize_.x), (texRectTilePos_.y * texRectSize_.y) };
	texPosOffset = texOffset_;
	texRectSize = texRectSize_;

	vel = vel_;
}
sf::IntRect rec::getTexRect()
{
	return { {(int)texRectPos.x,(int)texRectPos.y},{(int)texRectSize.x,(int)texRectSize.y} };
};

void rec::setTexRect(int col_, int row_)
{
	texRectPos = { col_ * texRectSize.x, row_ * texRectSize.y };
};

sf::Vector2f rec::getImagePos()
{
	return { pos.x - texPosOffset.x, pos.y - texPosOffset.y };
};

void rec::applyExternalForces()
{

}

void rec::tickPos()
{
	prevPos = pos;
	pos += vel * gTime;
};