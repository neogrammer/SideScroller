#ifndef ENEMY_H__
#define ENEMY_H__

#include <SFML/Graphics/RenderWindow.hpp>
#include <ai/enemy_scripts.h>
#include <ai/ScriptMgr.h>
#include <ai/Scriptable.h>
#include <ai/script_types.h>
#include <variant>
#include <core/Cfg.h>
#include <visual/AnimMgr.h>
#include <functional>
#include <string>
#include <core/rec.h>

class Enemy : public Scriptable , public rec
{
public:
	ai::Direction currDir;
	ScriptMgr scriptMgr;
	bool facingRight;

public:

	Enemy(sf::Vector2f pos_, sf::Vector2f size_, Cfg::Textures texType_, sf::Vector2i texRectTilePos_ = { 0,0 }, sf::Vector2i texRectSize_ = { 50,50 }, sf::Vector2i texOffset_ = { 0,0 }, sf::Vector2f vel_ = { 0.f,0.f });
	virtual ~Enemy();


	virtual std::variant<PlayerState, GoblinState> onEvent(GameEvent evt_) = 0;
	virtual sf::IntRect getAnimRect() = 0;
	virtual void input() = 0;
	virtual void update() = 0;
	virtual void updateLate() = 0;
	virtual void render() =0 ;
	virtual void faceLeft() = 0;
	virtual void faceRight() = 0;
	virtual void takeHit(int damage_) = 0;
	virtual void resetScriptSequence() = 0;
	virtual std::variant<PlayerState, GoblinState> pickState(GameEvent evt_, std::vector<std::variant<PlayerState, GoblinState> > possibles_) = 0;

};

#endif
