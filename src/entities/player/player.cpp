#include "Player.h"
#include <core/GameStateMgr.h>
#include <core/globals.h>

Player::Player()
	: rec{ { 200.f,700.f }, { 207.f,132.f }, Cfg::Textures::PlayerAtlas, { 0,0 }, { 207, 132 }, { 0,0 }, { 0.f,0.f } }
	, animMgr{ "assets/data/animations/actors/player.dat", std::bind(&Player::onEvent, this, std::placeholders::_1), AnimType::Player }
{
}

Player::~Player()
{
}

std::variant<PlayerState> Player::onEvent(GameEvent evt_)
{
	std::vector<PlayerState> possibleStates = {};
	possibleStates.reserve(int(PlayerState::Count));

	switch (std::get<PlayerState>(animMgr.transientState))
	{
	case PlayerState::Idle:
	{
		switch (evt_)
		{
			case GameEvent::StartedRunning:
			{
				possibleStates.push_back(PlayerState::Running);
			}
				break;
			default:
				break;
		}
	}
	break;
	case PlayerState::Running:
	{
		switch (evt_)
		{
			case GameEvent::StoppedRunning:
			{
				possibleStates.push_back(PlayerState::Idle);
			}
				break;
			default:
				break;
		}
	}
	break;
	case PlayerState::Attacking:
	{
	}
	break;
	case PlayerState::Dying:
	{
	}
	break;
	case PlayerState::Damaged:
	{
	}
	break;
	case PlayerState::Jumping:
	{
	}
	break;
	case PlayerState::PeakingJump:
	{
	}
	break;
	case PlayerState::Falling:
	{
	}
	break;
	case PlayerState::HangingFromEdge:
	{
	}
	break;
	case PlayerState::WallSliding:
	{
	}
	break;
	case PlayerState::Crouching:
	{
	}
	break;
	case PlayerState::Dashing:
	{
	}
	break;
	case PlayerState::DashAttacking:
	{
	}
	break;
	case PlayerState::Sliding:
	{
	}
	break;
	case PlayerState::LadderClimbing:
	{
	}
	break;
	case PlayerState::Count:
	{
	}
	break;
	default:
	{
	}
	break;
	}

	possibleStates.shrink_to_fit();
	if (possibleStates.size() == 1)
	{

		animMgr.changeAnimState(possibleStates[0]);
		return possibleStates[0];
		
	}


	return PlayerState::Count;
}

sf::IntRect Player::getAnimRect()
{
	return animMgr.getCurrentRect();
}

void Player::update()
{
	if (vel.x != 0.f || vel.y != 0.f || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		
		onEvent(GameEvent::StartedRunning);
		if (vel.x < 0.f || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			animMgr.faceLeft();
		}
		else if (vel.x > 0.f || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			animMgr.faceRight();
		}
	}

	pos += vel * gTime;
	if (pos.x < 10.f && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		onEvent(GameEvent::StoppedRunning);
		pos.x = 10.f;
	}
	if (pos.y < 550.f && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		onEvent(GameEvent::StoppedRunning);
		pos.y = 550.f;
	}
	if (pos.x > 900.f - size.y && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		onEvent(GameEvent::StoppedRunning);
		pos.y = 900.f - size.y;
	}
	if (pos.y > 900.f - size.y && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		onEvent(GameEvent::StoppedRunning);
		pos.y = 900.f - size.y;
	}
	if (vel.x == 0.f && vel.y == 0.f && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)  && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		onEvent(GameEvent::StoppedRunning);
	}
	

	animMgr.update();
}

void Player::updateLate()
{
	animMgr.updateLate();
}
