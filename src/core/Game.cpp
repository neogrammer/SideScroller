#include <core/Game.h>
#include <type_traits>
#include <string>
#include <variant>
#include <string>
#include <functional>
#include <utility>

Game::Game()
	: gameStateMgr{ std::make_unique<GameStateMgr>(this) }
{
	wndw::CreateWindow("MegamanOne", 1600U, 900U);
	gWnd.setPosition({ 120, 20 });
}

void Game::render()
{
	gameStateMgr->render();
}

void Game::input()
{
	gameStateMgr->input();
}

Game::~Game()
{
}

void Game::run()
{
	
	gTime = frameTimer.restart().asSeconds();
	
	
	// game loop
	while (gWnd.isOpen())
	{

		// window events handled here
		sf::Event e;
		while (gWnd.pollEvent(e))
		{
			if ((e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape) || e.type == sf::Event::Closed)
			{
				gWnd.close();
			}
			gameStateMgr->processEvent(e);
		}

		// if not closed, update and draw the game as needed
		if (gWnd.isOpen())
		{
			gPrevTime = gTime;
			gTime = frameTimer.restart().asSeconds();
			auto num = sf::Mouse::getPosition(gWnd);
			mpos = (sf::Vector2f)num;
		
			
			input();

			
			update();
			updateLate();
			// now render the screen
			gWnd.clear(sf::Color(47, 147, 247, 255));
			render();
			gWnd.display();

			
		}
	}
}

void Game::update()
{
	gameStateMgr->update();
}

void Game::updateLate()
{
	gameStateMgr->updateLate();
}

