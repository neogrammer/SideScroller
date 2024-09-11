#ifndef PLAYSTATE_H__
#define PLAYSTATE_H__
#include <core/GameStateMgr.h>
#include <core/GameState.h>
#include <SFML/Graphics/View.hpp>
#include <entities/player/Player.h>
#include <entities/enemies/goblin/Goblin.h>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <stack>
#include <memory>
#include <array>
#include <visual/AnimMgr.h>

#include <GUI/MenuObject.h>
#include <GUI/MenuMgr.h>
#include <hud/HUD.h>
class PlayState : public GameState
{
	friend class GameStateMgr;
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Goblin>> goblins;
	std::array<int, 5> bgLengthsTravelled = { 1,1,1,1,1 };
	std::string lastAction{ "" };
	//GUI
	MenuObject baseGUI;
	MenuMgr menuMgr;
	HUD hud;
	bool menuButtonDown{ false };
	bool menuButtonReleased{ false };
	bool confirmButtonDown{ false };
	bool confirmButtonReleased{ false };
	bool cancelButtonDown{ false };
	bool cancelButtonReleased{ false };
	bool leftButtonDown{ false };
	bool leftButtonReleased{ false };
	bool rightButtonDown{ false };
	bool rightButtonReleased{ false };
	bool upButtonDown{ false };
	bool upButtonReleased{ false };
	bool downButtonDown{ false };
	bool downButtonReleased{ false };
	float commandTextElapsed{ 0.f };
	float commandTextDelay{ 2.f };

	int numGoblins{ 0 };

	void DrawBG();
	
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