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
			case GameEvent::StartedAttacking:
			{
				possibleStates.push_back(PlayerState::Attacking);
			}
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
			case GameEvent::StartedAttacking:
			{
				possibleStates.push_back(PlayerState::Attacking);
			}
			break;
			default:
				break;
		}
	}
	break;
	case PlayerState::Attacking:
	{
		switch (evt_)
		{
			case GameEvent::StoppedAttacking:
			{
				possibleStates.push_back(PlayerState::Idle);
				possibleStates.push_back(PlayerState::Running);
			}
				break;
			default:
				break;
		}

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
	else if (possibleStates.size() > 1)
	{
		auto tmp = pickState(evt_, possibleStates);
		animMgr.changeAnimState(tmp);
		return tmp;
	}


	return PlayerState::Count;
}

sf::IntRect Player::getAnimRect()
{
	return animMgr.getCurrentRect();
}

void Player::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//if (gWnd.mapCoordsToPixel({ (float)player->pos.x + (player->size.x / 2.f) + (300.f * gTime), player->pos.y }).x <= 800)
	 //	{
		vel.x = 400.f;
		//	}
			//else
			//{
			//	// move view
			//	player->vel.x = 0.f;
			//	MoveView(300.f);
			//}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//if (gWnd.mapCoordsToPixel({ (float)player->pos.x + (player->size.x / 2.f) - (300.f * gTime), player->pos.y }).x >= 800 || gameView.getCenter().x - (300.f * gTime) < 800.f)
		//{
		vel.x = -400.f;

		//if ((gWnd.mapCoordsToPixel({ player->pos.x + (player->size.x / 2.f) + (player->vel.x * gTime), player->pos.y }).x < 800) && (gameView.getCenter().x - (300.f * gTime) + (player->size.x / 2.f) > 800.f))
		//{
		//	// move view
		//	player->vel.x = 0.f;
		//	MoveView(-300.f);


		//}
	}
	else
	{
		vel.x = 0.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		vel.y = -400.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		vel.y = 400.f;
	}
	else
	{
		vel.y = 0.f;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		onEvent(GameEvent::StartedAttacking);
		vel.x = 0.f;
	}
	else
	{
		if (std::get<PlayerState>(animMgr.mainState) == PlayerState::Attacking)
		{
			stopAttacking = true;
			vel.x = 0.f;
		}
	}

	if (std::get<PlayerState>(animMgr.mainState) == PlayerState::Attacking && stopAttacking == true)
	{
		if (animMgr.animMap.currentAnimation->isOnLastFrame())
		{
			stopAttacking = false;
			onEvent(GameEvent::StoppedAttacking);
		}
	}


	pos += vel * gTime;
	if (vel.x < 0.f && pos.x + (size.x / 2.f) > gameView.getCenter().x)
	{
		// do nothing
	}
	else if (vel.x < 0.f && pos.x + (size.x / 2.f) >= 800.f)
	{
		MoveView(vel.x);
		gameView.setCenter({ pos.x + (size.x / 2.f) , 450.f });
	}
	else if (vel.x < 0.f && pos.x + (size.x / 2.f) < 800.f)
	{
		gameView.setCenter({ 800.f,450.f });
	}

	if (vel.x > 0.f && pos.x + (size.x / 2.f) < gameView.getCenter().x)
	{
		// do nothing
	}
	else if (vel.x > 0.f && pos.x + (size.x / 2.f) <= 25000.f - 800.f)
	{
		MoveView(-vel.x);
		gameView.setCenter({ pos.x + (size.x / 2.f) , 450.f });
	}
	else if (vel.x > 0.f && pos.x + (size.x / 2.f) > 25000.f - 800.f)
	{
		gameView.setCenter({ 25000.f - 800.f,450.f });
	}
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

	//pos += vel * gTime;
	if (pos.x < 10.f && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//onEvent(GameEvent::StoppedRunning);
		pos.x = 10.f;
	}
	if (pos.y > 900.f - size.y && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//onEvent(GameEvent::StoppedRunning);
		pos.y = 900.f - size.y;
	}
	if (pos.y < 550.f && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//onEvent(GameEvent::StoppedRunning);
		pos.y = 550.f;
	}
	if (pos.x > 25000.f - 10.f && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//onEvent(GameEvent::StoppedRunning);
		pos.x = 25000.f - 10.f;
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

void Player::MoveView(float xVelocity)
{
	gWnd.setView(gameView);


	// move map and then put the player at the center of the screen
	//gameView.move({xVelocity * gTime, 0.f});
	std::stack<std::unique_ptr<sf::Sprite> > tmpStack = {};
	std::stack<std::unique_ptr<sf::Sprite> > tmpLoopStack = {};

	int numLayers = (int)bgLayers.size();

	tmpStack.push(std::move(bgLayers.top()));
	bgLayers.pop();
	tmpStack.top()->move({ ((80000.f / xVelocity) * gTime) , 0.f });
	loopLayers.top()->setPosition({ tmpStack.top()->getPosition().x + 4500.f, tmpStack.top()->getPosition().y });
	tmpLoopStack.push(std::move(loopLayers.top()));
	loopLayers.pop();

	tmpStack.push(std::move(bgLayers.top()));
	bgLayers.pop();
	tmpStack.top()->move({ ((75000.f / xVelocity) * gTime) , 0.f });
	loopLayers.top()->setPosition({ tmpStack.top()->getPosition().x + 4500.f, tmpStack.top()->getPosition().y });
	tmpLoopStack.push(std::move(loopLayers.top()));
	loopLayers.pop();

	tmpStack.push(std::move(bgLayers.top()));
	bgLayers.pop();
	tmpStack.top()->move({ ((50000.f / xVelocity) * gTime) , 0.f });
	loopLayers.top()->setPosition({ tmpStack.top()->getPosition().x + 4500.f, tmpStack.top()->getPosition().y });
	tmpLoopStack.push(std::move(loopLayers.top()));
	loopLayers.pop();


	tmpStack.push(std::move(bgLayers.top()));
	bgLayers.pop();
	tmpStack.top()->move({ ((40000.f / xVelocity) * gTime) , 0.f });
	loopLayers.top()->setPosition({ tmpStack.top()->getPosition().x + 4500.f, tmpStack.top()->getPosition().y });
	tmpLoopStack.push(std::move(loopLayers.top()));
	loopLayers.pop();


	tmpStack.push(std::move(bgLayers.top()));
	bgLayers.pop();
	tmpStack.top()->move({ ((20000.f / xVelocity) * gTime) , 0.f });
	loopLayers.top()->setPosition({ tmpStack.top()->getPosition().x + 4500.f, tmpStack.top()->getPosition().y });
	tmpLoopStack.push(std::move(loopLayers.top()));
	loopLayers.pop();

	/*	tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		tmpStack.top()->move({ (-xVelocity * gTime) + (xVelocity * 0.9999f * gTime) , 0.f });
		loopLayers.top()->setPosition({ tmpStack.top()->getPosition().x + 4500.f, tmpStack.top()->getPosition().y });
		tmpLoopStack.push(std::move(loopLayers.top()));
		loopLayers.pop();

		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		tmpStack.top()->move({ (-xVelocity * gTime) + (xVelocity * .6f * gTime) , 0.f });
		loopLayers.top()->setPosition({ tmpStack.top()->getPosition().x + 4500.f, tmpStack.top()->getPosition().y });
		tmpLoopStack.push(std::move(loopLayers.top()));
		loopLayers.pop();

		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		tmpStack.top()->move({ (-xVelocity * gTime) + (xVelocity * 0.3f * gTime) , 0.f });
		loopLayers.top()->setPosition({ tmpStack.top()->getPosition().x + 4500.f, tmpStack.top()->getPosition().y });
		tmpLoopStack.push(std::move(loopLayers.top()));
		loopLayers.pop();


		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		tmpStack.top()->move({ (-xVelocity * gTime) + (xVelocity * 0.2f * gTime) , 0.f });
		loopLayers.top()->setPosition({ tmpStack.top()->getPosition().x + 4500.f, tmpStack.top()->getPosition().y });
		tmpLoopStack.push(std::move(loopLayers.top()));
		loopLayers.pop();


		tmpStack.push(std::move(bgLayers.top()));
		bgLayers.pop();
		tmpStack.top()->move({ (-xVelocity * gTime) + (xVelocity * 0.0001f * gTime) , 0.f });
		loopLayers.top()->setPosition({ tmpStack.top()->getPosition().x + 4500.f, tmpStack.top()->getPosition().y });
		tmpLoopStack.push(std::move(loopLayers.top()));
		loopLayers.pop();*/


	for (int i = 0; i < numLayers; i++)
	{
		bgLayers.push(std::move(tmpStack.top()));
		tmpStack.pop();
		loopLayers.push(std::move(tmpLoopStack.top()));
		tmpLoopStack.pop();
	}


	//player->vel.x = 0.f;
	//if (xVelocity < 0.f)
	//{
	//	player->pos = sf::Vector2f{ gWnd.mapPixelToCoords({ 800, (int)player->pos.y }).x - (player->size.x / 2.f), player->pos.y };
	//}
	//else if (xVelocity > 0.f)
	//{
	//	auto pos = sf::Vector2f{ gWnd.mapPixelToCoords({800 ,gWnd.mapCoordsToPixel(player->pos).y }).x - player->size.x / 2.f , player->pos.y };

	//	auto diff = (player->pos.x - pos.x) - ((int)((player->pos.x - pos.x) * 100.f) % 2 == 1) ? (xVelocity * gTime) : 0.f;// std::roundf((xVelocity * gTime)); //{ gWnd.mapPixelToCoords({ 800, (int)player->pos.y }).x - (player->size.x / 2.f) + 0.5f, player->pos.y };
	//	pos.x += diff;
	//	player->pos = pos;
	//}
}

std::variant<PlayerState> Player::pickState(GameEvent evt_, std::vector<PlayerState>& possibles_)
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

	return possibles_[0];
}
