#include "PlayState.h"
#include <core/globals.h>
#include <type_traits>
#include <string>
#include <iostream>


void PlayState::input()
{
	if (!menuMgr.isOpen())
		player->input();
}

void PlayState::update()
{

	if (!menuMgr.isOpen())
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
		bool inRange = false;
		if (!goblin->deaddead)
		{
			
			inRange = goblin->checkAttackable(*player);
			if (!inRange)
			{
				if (goblin->isAttacking)
				{
					goblin->isAttacking = false;
					goblin->onEvent(GameEvent::StoppedAttacking);
				}
				goblin->checkForPlayer(*player);
			}
			if (inRange)
			{
				if (!goblin->isAttacking)
				{
					goblin->isAttacking = true;
					goblin->scriptMgr.breakOut();
					goblin->onEvent(GameEvent::StartedAttacking);
				}
			}


			if (goblin->isAttacking && goblin->isOnDamageFrame() && player->getHealth() > 0)
			{
				
				rec attackBox{ goblin->getAttackBox().getPosition(), goblin->getAttackBox().getSize(), player->texType, {0,0}, {0,0},{0,0}, { 0.f,0.f } };
				if (phys::RectVsRect(attackBox, *player))
				{
					if (goblin->pos.y + goblin->size.y > player->pos.y + player->size.y - 60.f && goblin->pos.y + goblin->size.y < player->pos.y + player->size.y + 60.f && !player->hitCooldownActive)
					{
						Player* ply;
						ply = player.get();
						goblin->damagePlayer(*ply);
						std::unique_ptr<sf::Text> dmg{};
						dmg = std::make_unique<sf::Text>();
						dmg->setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
						dmg->setString("10");
						dmg->setCharacterSize(32U);
						dmg->setFillColor(sf::Color::Yellow);
						dmg->setPosition({ player->pos.x + (player->size.x / 2.f) + (float)gDamageNumbers.size() * 10.f, player->pos.y - 30.f - (float)gDamageNumbers.size() * 10.f });
						gDamageNumbers.push(std::move(dmg));
						gDmgElapsed.push(0.f);
					}
				}
			}

			goblin->update();

		}


		setLoopLayers();
	}


	menuButtonReleased = false;
	if (menuButtonDown)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			menuButtonReleased = true;
		}
	}
	confirmButtonReleased = false;
	if (confirmButtonDown)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			confirmButtonReleased = true;
		}
	}
	cancelButtonReleased = false;
	if (cancelButtonDown)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			cancelButtonReleased = true;
		}
	}
	leftButtonReleased = false;
	if (leftButtonDown)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			rightButtonReleased = true;
		}
	}
	rightButtonReleased = false;
	if (rightButtonDown)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			rightButtonReleased = true;
		}
	}
	upButtonReleased = false;
	if (upButtonDown)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			upButtonReleased = true;
		}
	}
	downButtonReleased = false;
	if (downButtonDown)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			downButtonReleased = true;
		}
	}


	menuButtonDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		menuButtonDown = true;
	}
	confirmButtonDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		confirmButtonDown = true;
	}
	cancelButtonDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		cancelButtonDown = true;
	}
	leftButtonDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		leftButtonDown = true;
	}
	rightButtonDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rightButtonDown = true;
	}
	upButtonDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		upButtonDown = true;
	}
	downButtonDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		downButtonDown = true;
	}


	if (!menuMgr.isOpen())
	{
		if (menuButtonReleased)
		{
			menuMgr.open(&baseGUI["main"]);
			lastAction = "";
			commandTextElapsed = 0.f;
		}
	}
	else
	{
		if (menuButtonReleased)
			menuMgr.close();
		
		if (upButtonReleased)
			menuMgr.onUp();

		if (leftButtonReleased)
			menuMgr.onLeft();

		if (downButtonReleased)
			menuMgr.onDown();

		if (rightButtonReleased)
			menuMgr.onRight();



		MenuObject* command = nullptr;
		if (confirmButtonReleased)
			command = menuMgr.onConfirm();
		if (cancelButtonReleased)
		{
			menuMgr.onBack();
		}

		if (command != nullptr)
		{
			lastAction = "Selected: " + command->getName() + " ID: " + std::to_string(command->getID());
			 
			menuMgr.close();
		}
		
	}
}

void PlayState::updateLate()
{
	player->updateLate();
	//goblin->updateLate();
	if (!goblin->deaddead)
	{
		goblin->updateLate();
	}

}

void PlayState::render()
{
	gWnd.setView(gameView);
	DrawBG();

	//if (scriptMgr_.getDir() != animMgr_.getDirection())
	//{
	//	switch (scriptMgr_.front()->getDirection())
	//	{
	//	case Direction::D:
	//		animMgr_.setAnim(AnimName::WalkD);
	//		break;

	//	case Direction::U:
	//		animMgr_.setAnim(AnimName::WalkU);
	//		break;
	//	case Direction::R:
	//		animMgr_.setAnim(AnimName::WalkR);
	//		break;
	//	case Direction::L:
	//		animMgr_.setAnim(AnimName::WalkL);
	//		break;
	//	case Direction::DR:
	//		animMgr_.setAnim(AnimName::WalkDR);
	//		break;
	//	case Direction::DL:
	//		animMgr_.setAnim(AnimName::WalkDL);
	//		break;
	//	case Direction::UR:
	//		animMgr_.setAnim(AnimName::WalkUR);
	//		break;
	//	case Direction::UL:
	//		animMgr_.setAnim(AnimName::WalkUL);
	//		break;
	//	default:
	//		break;
	//	}
	//	animMgr_.setDirection(scriptMgr_.getDir());
	//	currDir_ = scriptMgr_.getDir();
	//}

	//scriptMgr_.render(l_wnd);


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
	//baseGUI["main"].render({500,400});
	menuMgr.render({ 500,500 });
	
	if (lastAction != "" && commandTextElapsed < commandTextDelay)
	{
	
		commandTextElapsed += gTime;
	
		sf::Text cmdTxt{ sf::Text{} };
		cmdTxt.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
		cmdTxt.setCharacterSize(44U);
		cmdTxt.setString(lastAction);
		cmdTxt.setPosition({ 200.f, 700.f });
		cmdTxt.setFillColor(sf::Color::Yellow);
		
		gWnd.draw(cmdTxt);
	}
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
	baseGUI["main"].setTable(1,4);
	baseGUI["main"]["Attack"].setTable(3,3).setID(101).setName("Attack");
	baseGUI["main"]["Attack"]["Arts"].setTable(2, 4).setID(301).setName("Arts");
	auto& arts = baseGUI["main"]["Attack"]["Arts"];
	arts["Swift Slash"].setID(403).enable(false);
	baseGUI["main"]["Magic"].setID(102).enable(false);
	baseGUI["main"]["Defend"].setID(103);
	baseGUI["main"]["Items"].setID(104);
	baseGUI["main"]["Escape"].setID(105);
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
