#ifndef SCRIPT_H__
#define SCRIPT_H__

#include <SFML/Graphics/RenderWindow.hpp>
#include <ai/script_types.h>
class Script
{
protected:
	ai::Direction dir{ ai::Direction::NotSet };
public:
	Script();
	virtual ~Script();

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void execute() = 0;

	virtual bool isDone() = 0;
	ai::Direction getDirection() {

		return dir;
	}
};

#endif