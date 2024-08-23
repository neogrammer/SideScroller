#include "PlayState.h"
#include <core/globals.h>
#include <type_traits>
#include <string>
#include <iostream>




void PlayState::input()
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (gWnd.mapCoordsToPixel({ (float)player->pos.x + (player->size.x / 2.f) + (300.f * gTime), player->pos.y }).x <= 800)
		{
			player->vel.x = 300.f;
		}
		else
		{
			// move view
			player->vel.x = 0.f;
			MoveView(300.f);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (gWnd.mapCoordsToPixel({ (float)player->pos.x + (player->size.x / 2.f) - (300.f * gTime), player->pos.y }).x >= 800)
		{
			player->vel.x = -300.f;
		}
		else
		{
			// move view
			// move view
			player->vel.x = 0.f;
			MoveView(-300.f);
		}

	}
	else
	{
		player->vel.x = 0.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
			player->vel.y = -300.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{

		
		player->vel.y = 300.f;
	}
	else
	{
		player->vel.y = 0.f;
	}
}



void PlayState::update()
{
	player->pos += player->vel * gTime;

	//AdjustView();
}

void PlayState::render()
{

	gWnd.setView(gameView);

	DrawBG();
	gWnd.draw(*phys::spr(*player));
	DrawFront();
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
			loopTop->setPosition({ 0.f, 900 - (float)top->getTextureRect().height });
		

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
				loopTop->setPosition({ 0.f, 900 - (float)top->getTextureRect().height });

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
				loopTop->setPosition({ 0.f, 650 - (float)top->getTextureRect().height });

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
				loopTop->setPosition({ 0.f, 650 - (float)top->getTextureRect().height });
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
				loopTop->setPosition({ 0.f, 500 - (float)top->getTextureRect().height });
			}
		}

	}

}

void PlayState::DrawBG()
{
	// draw bg onto current view at global position starting from zero
	int numLayers = (int)bgLayers.size()-1;
	std::stack<std::unique_ptr<sf::Sprite> > tmpStack = {};

	for (int i = 0; i < numLayers; i++)
	{
		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		gWnd.draw(*tmpStack.top());
	}
	// now lay them on the screen from back to front
	for (int i = 0; i < numLayers; i++)
	{
		bgLayers.push(std::move(tmpStack.top()));
		tmpStack.pop();
		//gWnd.draw(*bgLayers.top());
	}

	if (bgLayers.size()-1 != numLayers)
		std::cout << "bgLayers are not displaying properly" << std::endl;
}

void PlayState::DrawFront()
{
	// draw bg onto current view at global position starting from zero
	int numLayers = (int)bgLayers.size();
	std::stack<std::unique_ptr<sf::Sprite> > tmpStack = {};

	for (int i = 0; i < numLayers; i++)
	{
		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		if (i == numLayers - 1)
		{
			gWnd.draw(*tmpStack.top());
		}
	}
	// now lay them on the screen from back to front
	for (int i = 0; i < numLayers; i++)
	{
		bgLayers.push(std::move(tmpStack.top()));
		tmpStack.pop();
		//gWnd.draw(*bgLayers.top());
	}

	if (bgLayers.size() != numLayers)
		std::cout << "bgLayers are not displaying properly" << std::endl;
}

void PlayState::AdjustView()
{
	if (player->pos.x + player->size.x / 2.f > gameView.getCenter().x && gameView.getCenter().x < 4500.f - 800.f)
	{
		gameView.setCenter({ player->pos.x + player->size.x / 2.f , gameView.getCenter().y });
	}
	if (player->pos.x + player->size.x / 2.f < gameView.getCenter().x && gameView.getCenter().x > 800.f)
	{
		gameView.setCenter({ player->pos.x + player->size.x / 2.f , gameView.getCenter().y });
	}
}

void PlayState::MoveView(float xVelocity)
{
	gWnd.setView(gameView);


	// move map and then put the player at the center of the screen
	gameView.move({xVelocity * gTime, 0.f});
	std::stack<std::unique_ptr<sf::Sprite> > tmpStack;
	int numLayers = (int)bgLayers.size();

		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		tmpStack.top()->move({ (-xVelocity * gTime) + (xVelocity * 0.9999f * gTime) , 0.f });

		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		tmpStack.top()->move({ (-xVelocity * gTime) + (xVelocity * .9f * gTime) , 0.f });


		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		tmpStack.top()->move({ (-xVelocity * gTime) + (xVelocity * 0.7f * gTime) , 0.f });


		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		tmpStack.top()->move({ (-xVelocity * gTime) + (xVelocity * 0.5f * gTime) , 0.f });



		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		tmpStack.top()->move({ (-xVelocity * gTime) + (xVelocity * 0.1f * gTime) , 0.f });



	for (int i = 0; i < numLayers; i++)
	{
		bgLayers.push(std::move(tmpStack.top()));
		tmpStack.pop();
	}


	player->vel.x = 0.f;
	if (xVelocity < 0.f)
	{
		player->pos = { gWnd.mapPixelToCoords({ 800, (int)player->pos.y }).x - (player->size.x / 2.f), player->pos.y };
	}
	else if (xVelocity > 0.f)
	{
		auto pos = sf::Vector2f{ gWnd.mapPixelToCoords({800 ,gWnd.mapCoordsToPixel(player->pos).y }).x - player->size.x / 2.f , player->pos.y };

		auto diff = (player->pos.x - pos.x) - ((int)((player->pos.x - pos.x) * 100.f) % 2 == 1) ? (xVelocity * gTime) : 0.f;// std::roundf((xVelocity * gTime)); //{ gWnd.mapPixelToCoords({ 800, (int)player->pos.y }).x - (player->size.x / 2.f) + 0.5f, player->pos.y };
		pos.x += diff;
		player->pos = pos;
		//std::cout << "PlayerPos: " << player->pos.x << "\nPlayer Pos Calculation: " << (int)(800 - player->size.x / 2.f);
		//std::cout << std::endl;
	}
	//player->pos.x = player->pos.x;
	//auto adjust = ((player->size.x / 2.f) + player->texPosOffset.x);
	//player->pos.x += adjust;

}

void PlayState::setLoopLayers()
{
	int numLayers = (int)bgLayers.size();
	std::stack<std::unique_ptr<sf::Sprite> > tmpStack = {};
	std::stack<std::unique_ptr<sf::Sprite> > tmpLoopStack = {};

	for (int i = 0; i < numLayers; i++)
	{
		loopLayers.top()->setPosition({ bgLayers.top()->getPosition().x + (float)bgLayers.top()->getTextureRect().width, bgLayers.top()->getPosition().y});
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

PlayState::PlayState(GameStateMgr* mgr_)
	: GameState{ mgr_ }
	, player{std::make_unique<rec>()}
{
	player->set({ 200.f,700.f }, { 207.f,132.f }, Cfg::Textures::PlayerAtlas, { 0,0 }, { 207, 132 }, { 0,0 }, { 0.f,0.f });
}
