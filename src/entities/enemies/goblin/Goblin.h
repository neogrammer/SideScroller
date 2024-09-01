#ifndef GOBLIN_H__
#define GOBLIN_H__
#include <entities/enemies/Enemy.h>

class Goblin : public Enemy
{
public:
	std::function<std::variant<PlayerState, GoblinState>(GameEvent evt_)> Func;
	AnimMgr animMgr;
	bool facingRight{ true };
	bool stopAttacking{ false };
	std::unique_ptr<sf::Sound> screamSnd;
	std::unique_ptr<sf::Sound> hitSnd;


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

	std::variant<PlayerState, GoblinState> onEvent(GameEvent evt_) override final;
	sf::IntRect getAnimRect() override final;
	void input() override final;
	void update() override final;
	void updateLate() override final;
	void render() override final;
	void faceLeft() override final;
	void faceRight() override final;
	void takeHit(int damage_) override final;
	void resetScriptSequence() override final;
	std::variant<PlayerState, GoblinState> pickState(GameEvent evt_, std::vector<std::variant<PlayerState, GoblinState> > possibles_) override final;

};

#endif