#include "Goblin.h"
#include <core/globals.h>
#include <iostream>
#include <entities/player/player.h>

Goblin::Goblin(sf::Vector2f pos_)
	: Enemy{ pos_, { 46.f, 62.f }, Cfg::Textures::GoblinAtlas, { 0,0 }, { 300, 300 }, { 129,140}, { 0.f,0.f } }
	, animMgr{ "assets/data/animations/actors/enemies/goblin.dat", std::bind(&Goblin::onEvent, this, std::placeholders::_1), AnimType::Goblin }
	, health{ 40 }
	, maxHealth{ 40 }
	, deaddead{false}
	, screamSnd{}
	, hitSnd{}
	, playerSpotted{false}
	, playerInAttackRange{false}
	, isAttacking{false}
{
	screamSnd = std::make_unique<sf::Sound>();
	hitSnd = std::make_unique<sf::Sound>();
	wasHitSnd = std::make_unique<sf::Sound>();
	swordSwingSnd = std::make_unique<sf::Sound>();

	screamSnd->setBuffer(Cfg::sounds.get((int)Cfg::Sounds::GoblinDeath));
	hitSnd->setBuffer(Cfg::sounds.get((int)Cfg::Sounds::GoblinHurt));
	wasHitSnd->setBuffer(Cfg::sounds.get((int)Cfg::Sounds::GoblinHit));
	swordSwingSnd->setBuffer(Cfg::sounds.get((int)Cfg::Sounds::Sword2));

	

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
		case GameEvent::Damaged:
		{
			possibleStates.push_back(GoblinState::Damaged);
			if (markedForDeath)
				possibleStates.push_back(GoblinState::Dying);
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
		case GameEvent::Damaged:
		{
			possibleStates.push_back(GoblinState::Damaged);
			if (markedForDeath)
				possibleStates.push_back(GoblinState::Dying);
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
			possibleStates.push_back(GoblinState::Running);
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

void Goblin::resetScriptSequence(rec& pos_)
{
	auto yTime = fabs((pos_.pos.y - pos.y) / runSpeed);
	auto xTime = fabs((pos_.pos.x - pos.x) / runSpeed);

	scriptMgr.addScript(new Enemy_Script::MoveTo{ *this, pos_,  runSpeed, xTime + yTime });
	if (pos.x - pos_.pos.x > 0) faceLeft();
	if (pos.x - pos_.pos.x < 0) faceRight();
	if (xTime != 0.f && yTime != 0.f)
	{
		onEvent(GameEvent::StartedRunning);
		
	}
	else
	{
		onEvent(GameEvent::StoppedRunning);

	}
}

bool Goblin::checkAttackable(Player& pos_)
{
	if (sqrt(pow(pos.y - pos_.pos.y, 2) + pow(pos.x - pos_.pos.x, 2)) < attackRange)
	{
		playerInAttackRange = true;
	}
	else
	{
		playerInAttackRange = false;
	}

	return playerInAttackRange;
}

bool Goblin::isOnDamageFrame()
{
	return animMgr.getCurrentIdx() == 6;
}

void Goblin::checkForPlayer(rec& pos_)
{
	if (health > 0 && !this->hitCooldownActive)
	{

		if (scriptMgr.front() == nullptr)
		{
			if (sqrtf(powf(pos.x - pos_.pos.x, 2) + powf(pos.y - pos_.pos.y, 2)) < detectRadius)
			{
				resetScriptSequence(pos_);
				onEvent(GameEvent::StartedRunning);
				playerSpotted = true;
				
			}
			else
			{
				onEvent(GameEvent::StoppedRunning);
			}
		}
		else
		{
			playerSpotted = false;
		}
	}
}

void Goblin::damagePlayer(Player& ply_)
{
	ply_.takeHit(10);
}

void Goblin::update()
{
	if (scriptMgr.front() != nullptr && health > 0 && !this->hitCooldownActive)
	{
		scriptMgr.update();
		if (scriptMgr.getFacing() == ai::Facing::Left)
		{
			faceLeft();
		}
		else
		{
			faceRight();
		}
	}

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
	if (isAttacking && animMgr.getCurrentIdx() == 3)
		swordSwingSnd->play();
	animMgr.updateLate();
}

void Goblin::render()
{
	
}

void Goblin::faceLeft()
{
	facingRight = false;
	animMgr.faceLeft();
}

void Goblin::faceRight()
{
	facingRight = true;
	animMgr.faceRight();
}

void Goblin::takeHit(int damage_)
{
	if (!hitCooldownActive)
	{
		health -= damage_;
		if (isAttacking)
		{
			isAttacking = false;
		}
		if (health <= 0)
		{
			hitCooldownActive = true;
			hitCooldownElapsed = 0.f;
			hitCooldown = 10000.f;
			markedForDeath = true;
			
			hitSnd->play();
		}
		else
		{
			hitCooldownActive = true;
			hitCooldownElapsed = 0.f;
			wasHitSnd->play();
			
		}
		onEvent(GameEvent::Damaged);
	}
}

sf::FloatRect Goblin::getAttackBox()
{
	
	if (facingRight)
	{
		return { { getImagePos().x + 115.f, getImagePos().y + 140.f},{112.f,82.f} };
	}
	else
	{
		return { { getImagePos().x + 65.f, getImagePos().y + 116.f},{112.f,82.f} };
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
		if (std::get<GoblinState>(animMgr.transientState) == GoblinState::Attacking)
		{
			if (evt_ == GameEvent::StoppedAttacking)
			{
				return possibles_[0];
			}
			else if (evt_ == GameEvent::Damaged)
			{
				if (health > 0)
					return possibles_[0];
				else
					return possibles_[1];
			}
			else
			{
				return possibles_[0];
			}
		}
		if (std::get<GoblinState>(animMgr.transientState) == GoblinState::Damaged)
		{
			if (evt_ == GameEvent::DamageCooldownEnded)
			{
				if (isAttacking)
				{
					return possibles_[2];
				}
				else
				{


					if (scriptMgr.front() == nullptr)
					{
						return possibles_[0];
					}
					else
					{
						return possibles_[1];
					}
				}
			}
			else
			{
				if (isAttacking)
				{
					return possibles_[2];
				}
				else
				{
					return possibles_[0];
				}
			}
		}
	}
	return possibles_[0];
}