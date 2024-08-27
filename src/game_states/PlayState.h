#ifndef PLAYSTATE_H__
#define PLAYSTATE_H__
#include <core/GameStateMgr.h>
#include <core/GameState.h>
#include <SFML/Graphics/View.hpp>
#include <entities/player/Player.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <stack>
#include <memory>
#include <array>
#include <visual/AnimMgr.h>
class PlayState : public GameState
{
	friend class GameStateMgr;




	std::unique_ptr<Player> player{};
	//float tmpTimer{};
	//float l1Factor{0.1f};
	//float l2Factor{0.25f};
	//float l3Factor{0.5f};
	//float l4Factor{0.75f};
	//float l5Factor{1.f};
	//bool playerIsInCenter{ false };
	//float mapXVelocity{ 0.0f };
	std::array<int, 5> bgLengthsTravelled = { 1,1,1,1,1 };
	
	


	void DrawBG();
	//void AdjustView();
	
	void setLoopLayers();
	void DrawFront();
public:

	void LoadLevel(int levelNum_ = 1);
	PlayState() = default;
	PlayState(GameStateMgr* mgr_);
	void processEvent(sf::Event& e) override final;
	virtual ~PlayState();
	virtual void input() override final;
	virtual void update() override final;
	void updateLate() override final;
	virtual void render() override final;

	

};

#endif