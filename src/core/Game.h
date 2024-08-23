#ifndef GAME_H__
#define GAME_H__
#include <SFML/Graphics/View.hpp>
#include<core/rec.h>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <core/GameStateMgr.h>
#include <core/globals.h>
class Tilemap;

class Game
{
	std::unique_ptr<GameStateMgr> gameStateMgr{};
	sf::Clock frameTimer{};

	void input();
	void update();
	void render();

public:

	Game();
	~Game();
	void run();
};

#endif