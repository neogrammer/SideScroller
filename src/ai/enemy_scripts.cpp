#include <ai/enemy_scripts.h>
#include <iostream>
#include <core/globals.h>
using namespace ai;

Enemy_Script::MoveRight::MoveRight(rec& l_spr, float l_speed, float l_duration)
	: spr{ l_spr }
	, speed{ l_speed }
	, duration{ l_duration }
	, displacement{ 0.f }
	, dt{ 0.f }
{
	dir = Direction::R;
}

Enemy_Script::MoveRight::~MoveRight()
{
}

void Enemy_Script::MoveRight::execute()
{
	spr.pos=spr.pos+sf::Vector2f{ displacement, 0.f };
}

void Enemy_Script::MoveRight::update()
{
	displacement = gTime * speed;
	dt += gTime;

	if (dt < duration)
	{
		execute();
	}
}

void Enemy_Script::MoveRight::render()
{
}

bool Enemy_Script::MoveRight::isDone()
{
	return dt >= duration;
}



Enemy_Script::MoveLeft::MoveLeft(rec& l_spr, float l_speed, float l_duration)
	: spr{ l_spr }
	, speed{ l_speed }
	, duration{ l_duration }
	, displacement{ 0.f }
	, dt{ 0.f }
{
	dir = Direction::L;
}

Enemy_Script::MoveLeft::~MoveLeft()
{
}

void Enemy_Script::MoveLeft::execute()
{
	spr.pos=spr.pos+sf::Vector2f{ -1.f * displacement, 0.f };
}

void Enemy_Script::MoveLeft::update()
{
	displacement = gTime * speed;
	dt += gTime;

	if (dt < duration)
	{
		execute();
	}
}

void Enemy_Script::MoveLeft::render()
{
}

bool Enemy_Script::MoveLeft::isDone()
{
	return dt >= duration;
}


Enemy_Script::MoveTo::MoveTo(rec& from_, rec& to_, float l_speed, float l_duration)
	: from{ from_}
	, to{to_}
	, speed{ l_speed }
	, duration{ l_duration }
	, displacement{ 0.f }
	, dt{ 0.f }
{
	dir = Direction::U;
}

Enemy_Script::MoveTo::~MoveTo()
{
}

void Enemy_Script::MoveTo::execute()
{
	auto len = sqrtf(powf(to.pos.y - from.pos.y, 2) + powf(to.pos.x - from.pos.x, 2));
	float xComponent = (to.pos.x - from.pos.x) / len;
	float yComponent = (to.pos.y - from.pos.y) /len;
	sf::Vector2f direc = { xComponent, yComponent };


	from.pos = from.pos + sf::Vector2f{direc.x* displacement, direc.y* displacement};
}

void Enemy_Script::MoveTo::update()
{
	displacement = gTime * speed;
	dt += gTime;

	if (dt < duration)
	{
		execute();
	}
}

void Enemy_Script::MoveTo::render()
{
}

bool Enemy_Script::MoveTo::isDone()
{
	return dt >= duration;
}





Enemy_Script::MoveUp::MoveUp(rec& l_spr, float l_speed, float l_duration)
	: spr{ l_spr }
	, speed{ l_speed }
	, duration{ l_duration }
	, displacement{ 0.f }
	, dt{ 0.f }
{
	dir = Direction::U;
}

Enemy_Script::MoveUp::~MoveUp()
{
}

void Enemy_Script::MoveUp::execute()
{
	spr.pos=spr.pos+sf::Vector2f{ 0.f, -1.f * displacement };
}

void Enemy_Script::MoveUp::update()
{
	displacement = gTime * speed;
	dt += gTime;

	if (dt < duration)
	{
		execute();
	}
}

void Enemy_Script::MoveUp::render()
{
}

bool Enemy_Script::MoveUp::isDone()
{
	return dt >= duration;
}



Enemy_Script::MoveDown::MoveDown(rec& l_spr, float l_speed, float l_duration)
	: spr{ l_spr }
	, speed{ l_speed }
	, duration{ l_duration }
	, displacement{ 0.f }
	, dt{ 0.f }
{
	dir = Direction::D;
}

Enemy_Script::MoveDown::~MoveDown()
{
}

void Enemy_Script::MoveDown::execute()
{
	spr.pos=spr.pos+sf::Vector2f{ 0.f,  displacement };
}

void Enemy_Script::MoveDown::update()
{
	displacement = gTime * speed;
	dt += gTime;

	if (dt < duration)
	{
		execute();
	}
}

void Enemy_Script::MoveDown::render()
{
}

bool Enemy_Script::MoveDown::isDone()
{
	return dt >= duration;
}


Enemy_Script::MoveUpRight::MoveUpRight(rec& l_spr, float l_speed, float l_duration)
	: spr{ l_spr }
	, speed{ l_speed }
	, duration{ l_duration }
	, displacement{ 0.f }
	, dt{ 0.f }
{
	dir = Direction::UR;
}

Enemy_Script::MoveUpRight::~MoveUpRight()
{
}

void Enemy_Script::MoveUpRight::execute()
{
	spr.pos=spr.pos+sf::Vector2f{ displacement, -1.f * displacement };
}

void Enemy_Script::MoveUpRight::update()
{
	displacement = gTime * speed;
	dt += gTime;

	if (dt < duration)
	{
		execute();
	}
}

void Enemy_Script::MoveUpRight::render()
{
}

bool Enemy_Script::MoveUpRight::isDone()
{
	return dt >= duration;
}



Enemy_Script::MoveUpLeft::MoveUpLeft(rec& l_spr, float l_speed, float l_duration)
	: spr{ l_spr }
	, speed{ l_speed }
	, duration{ l_duration }
	, displacement{ 0.f }
	, dt{ 0.f }
{
	dir = Direction::UL;
}

Enemy_Script::MoveUpLeft::~MoveUpLeft()
{
}

void Enemy_Script::MoveUpLeft::execute()
{
	spr.pos=spr.pos+sf::Vector2f{ -1.f * displacement, -1.f * displacement };
}

void Enemy_Script::MoveUpLeft::update()
{
	displacement = gTime * speed;
	dt += gTime;

	if (dt < duration)
	{
		execute();
	}
}

void Enemy_Script::MoveUpLeft::render()
{
}

bool Enemy_Script::MoveUpLeft::isDone()
{
	return dt >= duration;
}







Enemy_Script::MoveDownLeft::MoveDownLeft(rec& l_spr, float l_speed, float l_duration)
	: spr{ l_spr }
	, speed{ l_speed }
	, duration{ l_duration }
	, displacement{ 0.f }
	, dt{ 0.f }
{
	dir = Direction::DL;
}

Enemy_Script::MoveDownLeft::~MoveDownLeft()
{
}

void Enemy_Script::MoveDownLeft::execute()
{
	spr.pos=spr.pos+sf::Vector2f{ -1.f * displacement,  displacement };
}

void Enemy_Script::MoveDownLeft::update()
{
	displacement = gTime * speed;
	dt += gTime;

	if (dt < duration)
	{
		execute();
	}
}

void Enemy_Script::MoveDownLeft::render()
{
}

bool Enemy_Script::MoveDownLeft::isDone()
{
	return dt >= duration;
}



Enemy_Script::MoveDownRight::MoveDownRight(rec& l_spr, float l_speed, float l_duration)
	: spr{ l_spr }
	, speed{ l_speed }
	, duration{ l_duration }
	, displacement{ 0.f }
	, dt{ 0.f }
{
	dir = Direction::DR;
}

Enemy_Script::MoveDownRight::~MoveDownRight()
{
}

void Enemy_Script::MoveDownRight::execute()
{
	spr.pos=spr.pos+sf::Vector2f{ displacement,  displacement };
}

void Enemy_Script::MoveDownRight::update()
{
	displacement = gTime * speed;
	dt += gTime;

	if (dt < duration)
	{
		execute();
	}
}

void Enemy_Script::MoveDownRight::render()
{
}

bool Enemy_Script::MoveDownRight::isDone()
{
	return dt >= duration;
}
