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
	//goblin->update();
	if (gGroundMoved)
	{
		if (!goblin->deaddead)
			goblin->pos.x += gDistGroundMoved;

		gGroundMoved = false;
		gDistGroundMoved = 0.f;
	}

	if (player->isAttacking() && player->isOnDamageFrame() && !goblin->markedForDeath)
	{
		rec attackBox{ player->getAttackBox().getPosition(), player->getAttackBox().getSize(), player->texType, {0,0}, {0,0},{0,0}, { 0.f,0.f } };
		if (phys::RectVsRect(attackBox, *goblin))
		{
			if (player->pos.y + player->size.y > goblin->pos.y + goblin->size.y - 30.f && player->pos.y + player->size.y < goblin->pos.y + goblin->size.y + 30.f && !goblin->hitCooldownActive)
			{
				std::variant<Goblin*> gob;
				gob = (goblin.get());
				player->damageEnemy(gob);
				std::unique_ptr<sf::Text> dmg{};
				dmg = std::make_unique<sf::Text>();
				dmg->setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
				dmg->setString("10");
				dmg->setCharacterSize(32U);
				dmg->setFillColor(sf::Color::Red);
				dmg->setPosition({ goblin->pos.x + (goblin->size.x / 2.f) + (float)gDamageNumbers.size() * 10.f, goblin->pos.y - 30.f - (float)gDamageNumbers.size() * 10.f });
				gDamageNumbers.push(std::move(dmg));
				gDmgElapsed.push(0.f);
			}
		}
	}

	if (!goblin->deaddead)
		goblin->update();

	
	setLoopLayers();
}

void PlayState::updateLate()
{
	player->updateLate();
	//goblin->updateLate();
	if (!goblin->deaddead)
		goblin->updateLate();

}

void PlayState::render()
{
	gWnd.setView(gameView);
	DrawBG();


	if (player->pos.y + player->size.y > goblin->pos.y + goblin->size.y)
	{
		sf::Sprite aGoblinSpr;
		aGoblinSpr.setTexture(Cfg::textures.get((int)goblin->texType));
		aGoblinSpr.setTextureRect(goblin->getAnimRect());
		aGoblinSpr.setPosition(goblin->getImagePos());
		if (!goblin->deaddead)
			gWnd.draw(aGoblinSpr);


		sf::Sprite aSpr;
		aSpr.setTexture(Cfg::textures.get((int)player->texType));
		aSpr.setTextureRect(player->getAnimRect());
		aSpr.setPosition(player->getImagePos());
		gWnd.draw(aSpr);
	}
	else
	{

		sf::Sprite aSpr;
		aSpr.setTexture(Cfg::textures.get((int)player->texType));
		aSpr.setTextureRect(player->getAnimRect());
		aSpr.setPosition(player->getImagePos());
		gWnd.draw(aSpr);

		sf::Sprite aGoblinSpr;
		aGoblinSpr.setTexture(Cfg::textures.get((int)goblin->texType));
		aGoblinSpr.setTextureRect(goblin->getAnimRect());
		aGoblinSpr.setPosition(goblin->getImagePos());
		if (!goblin->deaddead)
			gWnd.draw(aGoblinSpr);
	}
	
	DrawFront();


	

	std::stack<std::unique_ptr<sf::Text>> txtTmp={};
	std::stack<float> elapTmp = {};
	while (!gDamageNumbers.empty())
	{
		std::cout << gDamageNumbers.top()->getPosition().x << std::endl;
		std::cout << gameView.getCenter().x << std::endl;

		gDamageNumbers.top()->setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
		
	//	gDamageNumbers.top()->setPosition((sf::Vector2f)gWnd.mapCoordsToPixel(gDamageNumbers.top()->getPosition()));
		gWnd.draw(*gDamageNumbers.top());
		gDmgElapsed.top() += gTime;
		if (gDmgElapsed.top() > gDmgDelay)
		{
			gDamageNumbers.pop();
			gDmgElapsed.pop();
			continue;
		}
		else
		{
			txtTmp.push(std::move(gDamageNumbers.top()));
			gDamageNumbers.pop();
			elapTmp.push(gDmgElapsed.top());
			gDmgElapsed.pop();
		}
	}



	while (!txtTmp.empty())
	{
		
			gDamageNumbers.push(std::move(txtTmp.top()));
			txtTmp.pop();
			gDmgElapsed.push(elapTmp.top());
			elapTmp.pop();
	}


	//gWnd.setView(gWnd.getDefaultView());

	//std::unique_ptr<sf::Text> dmg{};
	//dmg = std::make_unique<sf::Text>();
	//dmg->setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
	//dmg->setString("Booyakasha");
	//dmg->setCharacterSize(32U);
	//dmg->setFillColor(sf::Color::Red);
	//dmg->setPosition({ 500.f,500.f});
	//gWnd.draw(*dmg);
	gWnd.setView(gWnd.getDefaultView());
	baseGUI["main"].render({500,400});
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
	Cfg::music.get((int)Cfg::Music::Intro).play();

	// GUI SETUP TEST
	baseGUI["main"].setTable(1,10);
	baseGUI["main"]["Attack"].setID(101);
	baseGUI["main"]["Magic"].setID(102).enable(false);
	baseGUI["main"]["Defend"].setID(103);
	baseGUI["main"]["Items"].setID(104);
	baseGUI["main"]["Escape"].setID(105);
	baseGUI["main"]["DummyA"].setID(105);
	baseGUI["main"]["DummyB"].setID(105);
	baseGUI["main"]["DummyX"].setID(105);
	baseGUI["main"]["DummyGF"].setID(105);
	baseGUI["main"]["DummyGF"].setID(105);
	baseGUI["main"]["DummyS"].setID(105);
	baseGUI["main"]["DummyG"].setID(105);
	baseGUI["main"]["DummyY"].setID(105);
	baseGUI["main"]["DummyWQ"].setID(105);
	baseGUI["main"]["DummyT"].setID(105);
	baseGUI["main"]["DummyYY"].setID(105);
	

	baseGUI.build();


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
	, player{  }
	, goblin{ }
{
	player = std::make_unique<Player>();
	goblin = std::make_unique<Goblin>();

	goblin->faceLeft();
}
