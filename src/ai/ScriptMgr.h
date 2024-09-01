#ifndef SCRIPTMGR_H__
#define SCRIPTMGR_H__
#include <ai/Sequence.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <ai/script_types.h>
#include <queue>
class Script;
class ScriptMgr
{
	Sequence<Script*> act;
	ai::Direction currDir;
	void executeFront();
	bool isCurrentDone();
public:
	ScriptMgr();
	~ScriptMgr();

	void addScript(Script* action_);
	void rotate();
	ai::Direction getDir();

	void update();
	void render();

	Script* front();

};

#endif
