#ifndef SCRIPT_H__
#define SCRIPT_H__

#include <SFML/Graphics/RenderWindow.hpp>
#include <ai/script_types.h>
class Script
{
protected:
	bool needsToBreak{ false };
	ai::Direction dir{ ai::Direction::NotSet };
	ai::Facing facing{ ai::Facing::Left };
public:
	Script();
	virtual ~Script();

	virtual void update(ai::Facing& facing_) = 0;
	virtual void render() = 0;
	virtual void execute(ai::Facing& facing_) = 0;

	virtual bool isDone() = 0;

	ai::Direction getDirection() {

		return dir;
	}
	ai::Facing getFacing() {
		return facing;
	}
	virtual void breakOut() {
		needsToBreak = true;
	}

	virtual bool shouldBreakOut() {
		return false;
	}
};

#endif