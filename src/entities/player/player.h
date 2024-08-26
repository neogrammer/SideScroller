#ifndef PLAYER_H__
#define PLAYER_H__
#include <core/Cfg.h>
#include <visual/AnimMgr.h>
#include <functional>
#include <string>
#include <variant>
#include <core/rec.h>

class Player : public rec
{
	std::function<std::variant<PlayerState>(GameEvent evt_)> Func;
	AnimMgr animMgr;
	bool facingRight{ true };
	bool stopAttacking{ false };
	
	Dir direction{ Dir::Right };
public:
	Player();
	~Player();
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player(Player&&) = delete;
	Player& operator=(Player&&) = delete;

	std::variant<PlayerState> onEvent(GameEvent evt_);
	sf::IntRect getAnimRect();
	void input();
	void update();
	void updateLate();
	void MoveView(float xVelocity);
	void render();
	std::variant<PlayerState> pickState(GameEvent evt_, std::vector<PlayerState>& possibles_);

};

#endif