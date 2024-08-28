#ifndef PLAYER_H__
#define PLAYER_H__
#include <core/Cfg.h>
#include <visual/AnimMgr.h>
#include <functional>
#include <string>
#include <variant>
#include <core/rec.h>
class Goblin;

class Player : public rec
{
	std::function<std::variant<PlayerState, GoblinState>(GameEvent evt_)> Func;
	AnimMgr animMgr;
	bool facingRight{ true };
	bool stopAttacking{ false };

	Dir direction{ Dir::Right };
	std::unique_ptr<sf::Sound> sword1Snd{};
	std::unique_ptr<sf::Sound> sword2Snd{};


public:
	Player();
	~Player();
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player(Player&&) = delete;
	Player& operator=(Player&&) = delete;

	std::variant<PlayerState, GoblinState> onEvent(GameEvent evt_);
	sf::IntRect getAnimRect();
	void input();
	void update();
	void updateLate();
	void MoveView(float xVelocity);
	bool isAttacking();
	bool isOnDamageFrame();
	sf::FloatRect getAttackBox();


	void damageEnemy(std::variant<Goblin*> enemy);
	void render();
	std::variant<PlayerState, GoblinState> pickState(GameEvent evt_, std::vector<std::variant<PlayerState, GoblinState> > possibles_);

};

#endif