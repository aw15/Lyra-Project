#include "stdafx.h"
#include "Player.h"


Player::Player(Renderer * renderer) : Object(renderer)
{
	SetGraphic(IDLE_IMAGE);
}


Player::~Player()
{
}

void Player::Draw()
{
	renderer->DrawTexturedRectSeq(position, 100, color, renderer->GetTexture(currentImageName.c_str()), ((int)animationTime) % maxAnimationX, 0, maxAnimationX, maxAnimationY,0.1);
}

void Player::Update(float eTime)
{
	animationTime += eTime*5;

	position.x += dir.x*velocity.x*eTime;
	position.y += dir.y*velocity.y*eTime;
	position.z += dir.y*velocity.y*eTime;
}

void Player::HandleInput(const char key, KeyStatus status)
{
	Command* command = inputHandler.handleInput(key,status);

	if (dynamic_cast<MoveCommand*>(command) != nullptr)
	{
		cout << "move";
	}
	if (command)
		command->Execute(*this);
}

void Player::Move(const Vector3D & dir)
{

	if (playerState != State::AIRATTACK)
	{
		this->dir.x = dir.x;
		this->dir.y = dir.y;
		SetGraphic(RUN_IMAGE);
	}
}

void Player::Idle()
{
	playerState = State::IDLE;
	dir.x = 0;
	dir.x = 0;
	SetGraphic(IDLE_IMAGE);
}

void Player::AirAttack()
{
	if (playerState != State::RUN)
	{
		playerState = State::AIRATTACK;
		dir.x = 0;
		dir.x = 0;
		SetGraphic(AIR_ATTACK_IMAGE);
	}
}

void Player::SetGraphic(const unsigned int image)
{
	switch (image)
	{
	case IDLE_IMAGE:
		currentImageName = "player_idle1";
		maxAnimationX = 3;
		break;
	case RUN_IMAGE:
		currentImageName = "player_run";
		maxAnimationX = 6;
		break;
	case AIR_ATTACK_IMAGE:
		currentImageName = "player_airAttack1";
		maxAnimationX = 4;
		break;
	}
}


