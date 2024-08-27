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

	Dir direction{ Dir::Right };
public:

	Goblin(sf::Vector2f pos_ = {1500.f, 450.f });
	~Goblin();
	Goblin(const Goblin&) = delete;
	Goblin& operator=(const Goblin&) = delete;
	Goblin(Goblin&&) = delete;
	Goblin& operator=(Goblin&&) = delete;

	std::variant<PlayerState, GoblinState> onEvent(GameEvent evt_);
	sf::IntRect getAnimRect();
	void input();
	void update();
	void updateLate();
	void render();
	std::variant<PlayerState, GoblinState> pickState(GameEvent evt_, std::vector<std::variant<PlayerState, GoblinState> > possibles_);

};

#endif