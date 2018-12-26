#include "stdafx.h"
#include "Player.h"


Player::Player(Renderer * renderer) : Object(renderer)
{

	width = 1;
	height = 1;
	speed = { 0.1f,0.1f,0 };
	maxAnimationX = 1;
	maxAnimationY = 1;
	animationTime = 0.0f;
	playerState = State::IDLE;
	SetGraphic(IDLE_IMAGE);

	

}


Player::~Player()
{
}

void Player::Init()
{
	physics = new PhysicsComponent(position,width, height);
}

void Player::Draw()
{
	Vector3D pixelpos;
	physics->GetPosition(pixelpos);
	pixelpos.ToPixel();

	renderer->DrawTexturedRectSeq(pixelpos, TOPIXEL(width*height), color, renderer->GetTexture(currentImageName.c_str()), ((int)animationTime) % maxAnimationX, 0, maxAnimationX, maxAnimationY,0.1);
}

void Player::Update()
{
	animationTime += UPDATE_FREQUENCY*5;
	physics->Update(dir, speed);
}

void Player::HandleInput(const char key, KeyStatus status)
{
	Command* command = inputHandler.handleInput(key,status);

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
	dir.y= 0;
	SetGraphic(IDLE_IMAGE);
}

void Player::AirAttack()
{
	if (playerState != State::RUN)
	{
		playerState = State::AIRATTACK;
		dir.x = 0;
		dir.y = 0;
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


