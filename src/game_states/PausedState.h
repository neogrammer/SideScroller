#ifndef PAUSEDSTATE_H__
#define PAUSEDSTATE_H__
#include <core/GameStateMgr.h>
#include <core/GameState.h>
class PausedState : public GameState
{
public:
	PausedState(GameStateMgr* mgr_);
	virtual ~PausedState();
	void processEvent(sf::Event& e) override final;

	virtual void input()  override final;
	virtual void update()  override final;
	virtual void render()  override final;

};

#endif