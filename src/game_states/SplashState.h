#ifndef SPLASHSTATE_H__
#define SPLASHSTATE_H__
#include <core/GameStateMgr.h>
#include <core/GameState.h>
class SplashState : public GameState
{
public:
	SplashState(GameStateMgr* mgr_);
	virtual ~SplashState();
	void processEvent(sf::Event& e) override final;
	virtual void input()  override final;
	virtual void update()  override final;
	void updateLate() override final;
	virtual void render()  override final;

};

#endif