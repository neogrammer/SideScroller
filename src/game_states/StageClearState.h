#ifndef STAGECLEARSTATE_H__
#define STAGECLEARSTATE_H__
#include <core/GameStateMgr.h>
#include <core/GameState.h>
class StageClearState : public GameState
{

public:
	StageClearState() = default;
	StageClearState(GameStateMgr* mgr_);
	~StageClearState() override final;
	void processEvent(sf::Event& e) override final;

	void input()   override final;
	void update()   override final;
	void updateLate() override final;
	void render()   override final;

};

#endif