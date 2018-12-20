#include "stdafx.h"
#include "Player.h"


Player::Player(Renderer * renderer) : Object(renderer)
{
	states["idle"] = new IdleState;
	states["move"] = new MoveState;
	SetState("idle");
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

void Player::HandleInput(const char key, KEY_STATUS status)
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
	this->dir.x = dir.x;
	this->dir.y = dir.y;
	SetGraphic(RUN_IMAGE);
}

void Player::Idle()
{
	dir.x = 0;
	dir.x = 0;
	SetGraphic(IDLE_IMAGE);
}

void Player::AirAttack()
{
	SetGraphic(AIR_ATTACK_IMAGE);
}

void Player::SetGraphic(const int image)
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

void Player::SetState(string name)
{
	currentState = states[name];
	if (name == "idle")
	{
		SetGraphic(IDLE_IMAGE);
	}
	if (name == "run")
	{
		SetGraphic(RUN_IMAGE);
	}
}

