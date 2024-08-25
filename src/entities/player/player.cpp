#include "Player.h"

Player::Player()
	: animMgr{ "assets/data/animations/actors/player.dat", std::bind(&Player::onEvent, this, std::placeholders::_1) }
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
	}
	break;
	case PlayerState::Running:
	{
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
	case PlayerState::Falling:
	{
	}
	break;
	case PlayerState::HangingFromEdge:
	{
	}
	break;
	case PlayerState::WallKicking:
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
	return PlayerState::Count;
}