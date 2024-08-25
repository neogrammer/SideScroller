#include "StageClearState.h"
#include <core/globals.h>
StageClearState::StageClearState(GameStateMgr* mgr_)
	: GameState{mgr_}
{

}

StageClearState::~StageClearState()
{

}

void StageClearState::processEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased && e.key.code == (sf::Keyboard::Enter))
	{
		owner->resetState(GameStateType::Play);
		owner->changeState(GameStateType::Splash);
	}
}

void StageClearState::input()
{

}


void StageClearState::update()
{

}

void StageClearState::render()
{
	
	sf::RectangleShape stageClearScreen;
	stageClearScreen.setSize({ 1600.f,900.f });
	stageClearScreen.setPosition({ 0.f,0.f });
	stageClearScreen.setFillColor(sf::Color::Red);
	
	gWnd.draw(stageClearScreen);

	sf::Text stageWonText;
	stageWonText.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
	stageWonText.setString("Stage Cleared!\n Password: EatPussy4Hours\n  Don't forget your password!! \n\n Press any button to continue!");
	stageWonText.setCharacterSize(44U);
	stageWonText.setFillColor(sf::Color::White);
	stageWonText.setPosition({ 530.f, 300.f });

	gWnd.draw(stageWonText);
	stageWonText.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
}
