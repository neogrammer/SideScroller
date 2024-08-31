#include "Goblin.h"
#include <core/globals.h>
Goblin::Goblin(sf::Vector2f pos_)
	: rec{ pos_, { 46.f, 62.f }, Cfg::Textures::GoblinAtlas, { 0,0 }, { 300, 300 }, { 129,140}, { 0.f,0.f } }
	, animMgr{ "assets/data/animations/actors/enemies/goblin.dat", std::bind(&Goblin::onEvent, this, std::placeholders::_1), AnimType::Goblin }
	, health{ 40 }
	, maxHealth{ 40 }
	, deaddead{false}
	, screamSnd{}
	, hitSnd{}
{
	screamSnd = std::make_unique<sf::Sound>();
	hitSnd = std::make_unique<sf::Sound>();

	screamSnd->setBuffer(Cfg::sounds.get((int)Cfg::Sounds::GoblinDeath));
	hitSnd->setBuffer(Cfg::sounds.get((int)Cfg::Sounds::GoblinHurt));

	

}

Goblin::~Goblin()
{
}

std::variant<PlayerState, GoblinState> Goblin::onEvent(GameEvent evt_)
{
	std::vector<std::variant<PlayerState, GoblinState> > possibleStates = {};
	possibleStates.reserve(int(GoblinState::Count));

	switch (std::get<GoblinState>(animMgr.transientState))
	{
	case GoblinState::Idle:
	{
		switch (evt_)
		{
			case GameEvent::StartedRunning:
			{
				possibleStates.push_back(GoblinState::Running);
			}
			break;
			case GameEvent::StartedAttacking:
			{
				possibleStates.push_back(GoblinState::Attacking);
			}
			break;
			case GameEvent::Damaged:
			{
				possibleStates.push_back(GoblinState::Damaged);
				if (markedForDeath)
					possibleStates.push_back(GoblinState::Dying);
			}
			break;
			default:
				break;
		}
	}
	break;
	case GoblinState::Running:
	{
		switch (evt_)
		{
		case GameEvent::StoppedRunning:
		{
			possibleStates.push_back(GoblinState::Idle);
		}
		break;
		case GameEvent::StartedAttacking:
		{
			possibleStates.push_back(GoblinState::Attacking);
		}
		break;
		default:
		{

		}
			break;
		}
	}
	break;
	case GoblinState::Attacking:
	{
		switch (evt_)
		{
		case GameEvent::StoppedAttacking:
		{
			possibleStates.push_back(GoblinState::Idle);
			possibleStates.push_back(GoblinState::Running);
		}
		break;
		default:
		{
		}
			break;
		}

	}
	break;
	case GoblinState::Dying:
	{
		return GoblinState::Count;
	}
	break;
	case GoblinState::Damaged:
	{
		switch (evt_)
		{
		case GameEvent::DamageCooldownEnded:
		{
			possibleStates.push_back(GoblinState::Idle);
		}
		break;
		default:
		{
		}
		break;
		}
	}
	break;
	case GoblinState::Count:
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
	else if (possibleStates.size() > 1)
	{
		auto tmp = pickState(evt_, possibleStates);
		animMgr.changeAnimState(tmp);
		return tmp;
	}


	return PlayerState::Count;
}

sf::IntRect Goblin::getAnimRect()
{
	return animMgr.getCurrentRect();
}

void Goblin::input()
{
}

void Goblin::update()
{

	if (hitCooldownActive)
	{
		hitCooldownElapsed += gTime;

		if (markedForDeath)
		{
			if (hitCooldownElapsed >= 1.2f)
			{
				deaddead = true;
			}
		}
		if (hitCooldownElapsed >= hitCooldown)
		{
			hitCooldownActive = false;
			onEvent(GameEvent::DamageCooldownEnded);
		}
	}
	animMgr.update();
}

void Goblin::updateLate()
{

	animMgr.updateLate();
}

void Goblin::render()
{
}

void Goblin::faceLeft()
{
	animMgr.faceLeft();
}

void Goblin::faceRight()
{
	animMgr.faceRight();
}

void Goblin::takeHit(int damage_)
{
	if (!hitCooldownActive)
	{
		health -= damage_;

		if (health <= 0)
		{
			hitCooldownActive = true;
			hitCooldownElapsed = 0.f;
			hitCooldown = 10000.f;
			markedForDeath = true;
			
			screamSnd->play();
		}
		else
		{
			hitCooldownActive = true;
			hitCooldownElapsed = 0.f;

			hitSnd->play();
		}
		onEvent(GameEvent::Damaged);
	}
}

std::variant<PlayerState, GoblinState> Goblin::pickState(GameEvent evt_, std::vector<std::variant<PlayerState, GoblinState> > possibles_)
{
	if (std::holds_alternative<PlayerState>(possibles_[0]))
	{
		if (std::get<PlayerState>(animMgr.transientState) == PlayerState::Attacking)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				return possibles_[1];
			}
			else
			{
				return possibles_[0];
			}
		}
	}
	else if (std::holds_alternative<GoblinState>(possibles_[0]))
	{
		if (std::get<GoblinState>(animMgr.transientState) == GoblinState::Idle)
		{
			if (evt_ == GameEvent::Damaged)
			{
				return possibles_[1];
			}
			else
			{
				return possibles_[0];
			}
		}
	}
	return possibles_[0];
}