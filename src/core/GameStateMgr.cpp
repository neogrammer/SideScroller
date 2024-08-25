#include <core/GameStateMgr.h>

#include <game_states/PausedState.h>
#include <game_states/PlayState.h>
#include <game_states/SplashState.h>
#include <game_states/TitleState.h>
#include <game_states/StageClearState.h>
#include <core/globals.h>
#include <iostream>
GameStateMgr::GameStateMgr(Game* game_)
	: game{ game_ }
{
	stateMap.emplace(std::pair{ GameStateType::Splash, std::move(std::make_unique<SplashState>(this)) });
	stateMap.emplace(std::pair{ GameStateType::Title, std::move(std::make_unique<TitleState>(this)) });
	stateMap.emplace(std::pair{ GameStateType::Pause, std::move(std::make_unique<PausedState>(this)) });
	stateMap.emplace(std::pair{ GameStateType::Play, std::move(std::make_unique<PlayState>(this)) });
	stateMap.emplace(std::pair{ GameStateType::StageClearState, std::move(std::make_unique<StageClearState>(this)) });
	stateStack.push(stateMap.at(GameStateType::Splash).get());
	
}
GameStateMgr::~GameStateMgr()
{
	while (!stateStack.empty())
	{
		stateStack.pop();
	}
	stateMap.clear();
}

void GameStateMgr::renderUnder()
{
	std::stack<GameState*> tmpStack = {};
	while (!stateStack.empty())
	{
		tmpStack.push(stateStack.top());
		stateStack.pop();

	}

	// statestack is empty, lets put the states back, and render each one  as we do so as to render the under ones first
	while (!tmpStack.empty())
	{
		stateStack.push(tmpStack.top());
		tmpStack.pop();
		stateStack.top()->render();
	}

	// tmpStack is now empty again and all states on the stack have been rendered in order
	
}

bool GameStateMgr::hasUnder()
{
	return (stateStack.size() > 1);
}

void GameStateMgr::input()
{
	if (!needsToSwitchState)
		stateStack.top()->input();
	return;
}

void GameStateMgr::update()
{
	if (needsToSwitchState)
		safeStateSwitch();
	if (!needsToSwitchState)
		stateStack.top()->update();
	return;
}

void GameStateMgr::updateLate()
{
	stateStack.top()->updateLate();
}

void GameStateMgr::popTop()
{
	stateStack.pop();
}

void GameStateMgr::resetState(GameStateType type_)
{
	if (stateMap.find(type_) != stateMap.end())
	{
		stateMap.erase(stateMap.find(type_));
		stateMap.insert_or_assign(type_, std::make_unique<PlayState>(this));
	}

}

void GameStateMgr::render()
{
	if (!needsToSwitchState)
	{
		if (hasUnder())
		{
			renderUnder();
		}
		else
		{
			stateStack.top()->render();
		}
	}
	return;
}

void GameStateMgr::safeStateSwitch()
{
	if (needsToSwitchState)
	{
		needsToSwitchState = false;
		if (nextState == GameStateType::None)
		{
			std::cout << "Trying to change states to GameStateType::None!" << std::endl;
			return;
		}
		else
		{
			gameView = gWnd.getDefaultView();
			gWnd.setView(gWnd.getDefaultView());
			if (popOffCurrent)
				stateStack.pop();
			
			stateStack.push(stateMap.at(nextState).get());

			if (nextState == GameStateType::Play)
			{
				dynamic_cast<PlayState*>(stateStack.top())->LoadLevel();
			}
		}
		nextState = GameStateType::None;
		popOffCurrent = true;

		return;
	}
	return;
}

void GameStateMgr::processEvent(sf::Event& e_)
{
	stateStack.top()->processEvent(e_);
}

void GameStateMgr::changeState(GameStateType type_, bool popCurrent_)
{
	nextState = type_;
	popOffCurrent = popCurrent_;
	needsToSwitchState = true;
	return;
}
