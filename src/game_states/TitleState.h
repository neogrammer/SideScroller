#ifndef TITLESTATE_H__
#define TITLESTATE_H__
#include <core/GameStateMgr.h>
#include <core/GameState.h>
class TitleState : public GameState
{
public:
	TitleState(GameStateMgr* mgr_);
	virtual ~TitleState();
	void processEvent(sf::Event& e) override final;

	virtual void input()   override final;
	virtual void update()   override final;
	virtual void render()   override final;

};

#endif