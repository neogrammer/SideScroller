#include <ai/ScriptMgr.h>
#include <ai/Script.h>

using namespace ai;

void ScriptMgr::executeFront()
{
	if (!act.get().empty())
	{
		act.get().front()->execute(currFacing);
	}
}

bool ScriptMgr::isCurrentDone()
{
	if (!act.get().empty())
	{
		return act.get().front()->isDone();
	}
	else
	{
		return false;
	}
}

ScriptMgr::ScriptMgr()
	: act{}
	, currDir{ Direction::NotSet }
	, currFacing{Facing::Left}
{
}

ScriptMgr::~ScriptMgr()
{
	while (!act.get().empty())
	{
		delete act.get().front();
		act.get().front() = nullptr;
		act.get().pop();
	}
}

void ScriptMgr::addScript(Script* action_)
{
	act.pushScript(std::move(action_));
	if (currDir == Direction::NotSet)
	{
		currDir = act.get().front()->getDirection();
	}
	
}

void ScriptMgr::rotate()
{
	if (!act.get().empty())
	{
		act.get().pop();
	}
}

void ScriptMgr::update()
{

	if (!act.get().empty())
	{
		if (act.get().front()->shouldBreakOut())
		{
			act.get().pop();
			return;
		}
		act.get().front()->update(currFacing);

		if (act.get().front()->isDone())
		{
			act.get().pop();
			if (!act.get().empty())
			{
				currDir = act.get().front()->getDirection();
			}
			if (!act.get().empty())
			{
				currFacing = act.get().front()->getFacing();
			}
		}
	}
}

void ScriptMgr::render()
{
	if (!act.get().empty())
		act.get().front()->render();
}

Script* ScriptMgr::front()
{
	if (!act.get().empty())
		return act.get().front();
	else
		return nullptr;
}

Direction ScriptMgr::getDir()
{
	return currDir;
}

ai::Facing ScriptMgr::getFacing()
{
	return currFacing;
}

void ScriptMgr::breakOut()
{
	while (!act.get().empty())
	{
		act.get().pop();
	}
		
	return;
}
