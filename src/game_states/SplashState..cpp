
#include "SplashState.h"
#include <core/globals.h>
#include "PlayState.h"
SplashState::SplashState(GameStateMgr* mgr_)
	: GameState(mgr_)
{
}

SplashState::~SplashState()
{
}

void SplashState::processEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Enter)
		{
			owner->changeState(GameStateType::Play, true);
			
		}
	}
}

void SplashState::input()
{
	
}

void SplashState::update()
{
}

void SplashState::updateLate()
{
}

void SplashState::render()
{



	sf::Sprite logoScreen = {};
	logoScreen.setTexture(Cfg::textures.get((int)Cfg::Textures::Logo));
	gWnd.draw(logoScreen);
}