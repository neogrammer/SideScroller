#ifndef GOBLIN_H__
#define GOBLIN_H__
#include <core/Cfg.h>
#include <visual/AnimMgr.h>
#include <functional>
#include <string>
#include <variant>
#include <core/rec.h>

class Goblin : public rec
{
	std::function<std::variant<PlayerState, GoblinState>(GameEvent evt_)> Func;
	AnimMgr animMgr;
	bool facingRight{ true };
	bool stopAttacking{ false };

public:

	Goblin(sf::Vector2f pos_ = {1650.f, 650.f });
	~Goblin();
	Goblin(const Goblin&) = delete;
	Goblin& operator=(const Goblin&) = delete;
	Goblin(Goblin&&) = delete;
	Goblin& operator=(Goblin&&) = delete;
	bool markedForDeath{ false };
	int health{};
	int maxHealth{};
	Dir direction{ Dir::Right };
	float hitCooldown{ 0.3f };
	float hitCooldownElapsed{ 0.f };
	bool hitCooldownActive{ false };
	bool deaddead{ false };

	std::variant<PlayerState, GoblinState> onEvent(GameEvent evt_);
	sf::IntRect getAnimRect();
	void input();
	void update();
	void updateLate();
	void render();
	void faceLeft();
	void faceRight();
	void takeHit(int damage_);
	std::variant<PlayerState, GoblinState> pickState(GameEvent evt_, std::vector<std::variant<PlayerState, GoblinState> > possibles_);

};

#endif