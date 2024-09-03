
#include "TitleState.h"
#include <core/globals.h>

TitleState::TitleState(GameStateMgr* mgr_)
	: GameState(mgr_)
	, titleBG{ }
{
	titleBG = Cfg::Textures::Title;

	//titleBGSpr = sf::Sprite{};
	//titleBGSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::Title));
	//titleBGSpr.setPosition(400.f, 75.f);
}

TitleState::~TitleState()
{
}

void TitleState::processEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Enter)
		{
			owner->changeState(GameStateType::Play, true);
		}
	}
}

void TitleState::input()
{
}

void TitleState::update()
{
}

void TitleState::updateLate()
{
}

void TitleState::render()
{
	sf::Sprite titleBGSpr={};
	titleBGSpr.setTexture(Cfg::textures.get((int)titleBG));
	titleBGSpr.setPosition(400.f, 75.f);
	gWnd.draw(titleBGSpr);

	//sf::Sprite logoScreen = {};
	//logoScreen.setTexture(Cfg::textures.get((int)Cfg::Textures::Title));
	//gWnd.draw(logoScreen);
}




