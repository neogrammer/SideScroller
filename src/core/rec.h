#ifndef REC_H__
#define REC_H__
#include <SFML/Graphics/Rect.hpp>
#include <core/GameStateMgr.h>
#include <core/Cfg.h>
struct rec
{
	sf::Vector2f pos;
	sf::Vector2f prevPos;
	sf::Vector2f size;
	Cfg::Textures  texType;
	sf::Vector2i texRectPos;
	sf::Vector2i texPosOffset;
	sf::Vector2i texRectSize;
	sf::Vector2f vel;

	rec();
	~rec() = default;
	rec(const rec&) = default;
	rec(rec&&) = default;
	rec& operator=(const rec&) = default;
	rec& operator=(rec&&) = default;
	void set(sf::Vector2f pos_, sf::Vector2f size_, Cfg::Textures texType_, sf::Vector2i texRectTilePos_ = { 0,0 }, sf::Vector2i texRectSize_ = { 50,50 }, sf::Vector2i texOffset_ = { 0,0 }, sf::Vector2f vel_ = { 0.f,0.f });

	sf::IntRect getTexRect();

	void setTexRect(int col_, int row_);


	sf::Vector2f getImagePos();


	void applyExternalForces();


	void tickPos();

};
#endif