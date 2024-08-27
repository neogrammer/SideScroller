#include "PlayState.h"
#include <core/globals.h>
#include <type_traits>
#include <string>
#include <iostream>


void PlayState::input()
{

	player->input();
}

void PlayState::update()
{
	player->update();
	
	setLoopLayers();
}

void PlayState::updateLate()
{
	player->updateLate();
}

void PlayState::render()
{
	gWnd.setView(gameView);
	DrawBG();
	sf::Sprite aSpr;
	aSpr.setTexture(Cfg::textures.get((int)player->texType));
	aSpr.setTextureRect(player->getAnimRect());
	aSpr.setPosition(player->getImagePos());
	gWnd.draw(aSpr);
	DrawFront();
	gWnd.setView(gWnd.getDefaultView());
}

void PlayState::processEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::P)
	{
		owner->changeState(GameStateType::Pause, false);
	}
}

PlayState::~PlayState()
{

}

void PlayState::LoadLevel(int levelNum_)
{
	if (levelNum_ == 1)
	{
		// load level one data.

		// First load in the bg layers
		while (!bgLayers.empty())
		{
			bgLayers.pop();
		}
		while (!loopLayers.empty())
		{
			loopLayers.pop();
		}
		std::stack<std::unique_ptr<sf::Sprite> > tmpStack = {};
		std::stack<std::unique_ptr<sf::Sprite> > tmpLoopStack = {};

		for (int i = 0; i < 5; i++)
		{
			bgLayers.push(std::make_unique<sf::Sprite>());
			loopLayers.push(std::make_unique<sf::Sprite>());

			tmpStack.push(std::move(bgLayers.top()));
			tmpLoopStack.push(std::move(loopLayers.top()));

			bgLayers.pop();
			loopLayers.pop();
		}

		bgLayers.push(std::move(tmpStack.top()));
		loopLayers.push(std::move(tmpLoopStack.top()));

		tmpStack.pop();
		tmpLoopStack.pop();
		{
			auto& top = bgLayers.top();
			auto& loopTop = loopLayers.top();
			top->setTexture(Cfg::textures.get((int)Cfg::Textures::BG1_5));
			top->setPosition({ 0.f, 900 - (float)top->getTextureRect().height });
			loopTop->setTexture(Cfg::textures.get((int)Cfg::Textures::BG1_5));
			loopTop->setPosition({ 4500.f, 900 - (float)top->getTextureRect().height });
		}
		{
			auto& under = bgLayers.top();
			auto& underLoop = loopLayers.top();
			bgLayers.push(std::move(tmpStack.top()));
			loopLayers.push(std::move(tmpLoopStack.top()));
			tmpStack.pop();
			tmpLoopStack.pop();
			{
				auto& top = bgLayers.top();
				auto& loopTop = loopLayers.top();
				top->setTexture(Cfg::textures.get((int)Cfg::Textures::BG1_4));
				top->setPosition({ 0.f, 900 - (float)top->getTextureRect().height });
				loopTop->setTexture(Cfg::textures.get((int)Cfg::Textures::BG1_4));
				loopTop->setPosition({ 4500.f, 900 - (float)top->getTextureRect().height });
			}
		}
		{
			auto& under = bgLayers.top();
			auto& underLoop = loopLayers.top();
			bgLayers.push(std::move(tmpStack.top()));
			loopLayers.push(std::move(tmpLoopStack.top()));
			tmpStack.pop();
			tmpLoopStack.pop();
			{
				auto& top = bgLayers.top();
				auto& loopTop = loopLayers.top();
				top->setTexture(Cfg::textures.get((int)Cfg::Textures::BG1_3));
				top->setPosition({ 0.f, 650 - (float)top->getTextureRect().height });
				loopTop->setTexture(Cfg::textures.get((int)Cfg::Textures::BG1_3));
				loopTop->setPosition({ 4500.f, 650 - (float)top->getTextureRect().height });
			}
		}
		{
			auto& under = bgLayers.top();
			auto& underLoop = loopLayers.top();
			bgLayers.push(std::move(tmpStack.top()));
			loopLayers.push(std::move(tmpLoopStack.top()));
			tmpStack.pop();
			tmpLoopStack.pop();
			{
				auto& top = bgLayers.top();
				auto& loopTop = loopLayers.top();
				top->setTexture(Cfg::textures.get((int)Cfg::Textures::BG1_2));
				top->setPosition({ 0.f, 650 - (float)top->getTextureRect().height });
				loopTop->setTexture(Cfg::textures.get((int)Cfg::Textures::BG1_2));
				loopTop->setPosition({ 4500.f, 650 - (float)top->getTextureRect().height });
			}
		}
		{
			auto& under = bgLayers.top();
			auto& underLoop = loopLayers.top();
			bgLayers.push(std::move(tmpStack.top()));
			tmpStack.pop();
			loopLayers.push(std::move(tmpLoopStack.top()));
			tmpLoopStack.pop();
			{
				auto& top = bgLayers.top();
				auto& loopTop = loopLayers.top();
				top->setTexture(Cfg::textures.get((int)Cfg::Textures::BG1_1));
				top->setPosition({ 0.f, 500 - (float)top->getTextureRect().height });
				loopTop->setTexture(Cfg::textures.get((int)Cfg::Textures::BG1_1));
				loopTop->setPosition({ 4500.f, 500 - (float)top->getTextureRect().height });
			}
		}
	}
}

void PlayState::DrawBG()
{
	// draw bg onto current view at global position starting from zero
	int numLayers = (int)bgLayers.size()-1;
	std::stack<std::unique_ptr<sf::Sprite> > tmpStack = {};
	std::stack<std::unique_ptr<sf::Sprite> > tmpLoopStack = {};

	for (int i = 0; i < numLayers; i++)
	{
		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		gWnd.draw(*tmpStack.top());
		tmpLoopStack.push(std::move(loopLayers.top()));
		loopLayers.pop();
		gWnd.draw(*tmpLoopStack.top());
	}
	// now lay them on the screen from back to front
	for (int i = 0; i < numLayers; i++)
	{
		bgLayers.push(std::move(tmpStack.top()));
		tmpStack.pop();
		loopLayers.push(std::move(tmpLoopStack.top()));
		tmpLoopStack.pop();
	}

	if (bgLayers.size()-1 != numLayers)
		std::cout << "bgLayers are not displaying properly" << std::endl;
}

void PlayState::DrawFront()
{
	// draw bg onto current view at global position starting from zero
	int numLayers = (int)bgLayers.size();
	std::stack<std::unique_ptr<sf::Sprite> > tmpStack = {};
	std::stack<std::unique_ptr<sf::Sprite> > tmpLoopStack = {};

	for (int i = 0; i < numLayers; i++)
	{
		tmpStack.push(std::move(bgLayers.top()));
		tmpLoopStack.push(std::move(loopLayers.top()));

		bgLayers.pop();
		loopLayers.pop();

		if (i == numLayers - 1)
		{
			gWnd.draw(*tmpStack.top());
			gWnd.draw(*tmpLoopStack.top());

		}
	}
	// now lay them on the screen from back to front
	for (int i = 0; i < numLayers; i++)
	{
		bgLayers.push(std::move(tmpStack.top()));
		loopLayers.push(std::move(tmpLoopStack.top()));

		tmpStack.pop();
		tmpLoopStack.pop();
	}

	if (bgLayers.size() != numLayers)
		std::cout << "bgLayers are not displaying properly" << std::endl;
}

//void PlayState::AdjustView()
//{
//	if (player->pos.x + player->size.x / 2.f > gameView.getCenter().x && gameView.getCenter().x < 4500.f - 800.f)
//	{
//		gameView.setCenter({ player->pos.x + player->size.x / 2.f , gameView.getCenter().y });
//	}
//	if (player->pos.x + player->size.x / 2.f < gameView.getCenter().x && gameView.getCenter().x > 800.f)
//	{
//		gameView.setCenter({ player->pos.x + player->size.x / 2.f , gameView.getCenter().y });
//	}
//}


void PlayState::setLoopLayers()
{
	int numLayers = (int)bgLayers.size();
	std::stack<std::unique_ptr<sf::Sprite> > tmpStack = {};
	std::stack<std::unique_ptr<sf::Sprite> > tmpLoopStack = {};
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < numLayers; i++)
		{
			if (player->pos.x + (player->size.x / 2.f) + (player->vel.x * gTime) >=  loopLayers.top()->getPosition().x + 3700.f)
			{
				bgLengthsTravelled[i]++;
				bgLayers.top()->setPosition({ loopLayers.top()->getPosition() });
				loopLayers.top()->setPosition({ bgLayers.top()->getPosition().x + (float)bgLayers.top()->getTextureRect().width, bgLayers.top()->getPosition().y });
				
			}
			tmpStack.push(std::move(bgLayers.top()));
			bgLayers.pop();
			tmpLoopStack.push(std::move(loopLayers.top()));
			loopLayers.pop();
		}

		for (int i = 0; i < numLayers; i++)
		{
			bgLayers.push(std::move(tmpStack.top()));
			tmpStack.pop();
			loopLayers.push(std::move(tmpLoopStack.top()));
			tmpLoopStack.pop();
		}
	}	// background should now be reset
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{ 
		for (int i = 0; i < numLayers; i++)
		{
			if (player->pos.x + (player->size.x / 2.f) + (player->vel.x * gTime) < bgLayers.top()->getPosition().x + 800.f)
			{
				bgLengthsTravelled[i]--;
				loopLayers.top()->setPosition({ bgLayers.top()->getPosition() });
				bgLayers.top()->setPosition({ loopLayers.top()->getPosition().x - (float)loopLayers.top()->getTextureRect().width, loopLayers.top()->getPosition().y });
				
			}
			tmpStack.push(std::move(bgLayers.top()));
			bgLayers.pop();
			tmpLoopStack.push(std::move(loopLayers.top()));
			loopLayers.pop();
		}

		for (int i = 0; i < numLayers; i++)
		{
			bgLayers.push(std::move(tmpStack.top()));
			tmpStack.pop();
			loopLayers.push(std::move(tmpLoopStack.top()));
			tmpLoopStack.pop();
		}
	}
}
	
PlayState::PlayState(GameStateMgr* mgr_)
	: GameState{ mgr_ }
	, player{ std::make_unique<Player>() }
{
	
}
