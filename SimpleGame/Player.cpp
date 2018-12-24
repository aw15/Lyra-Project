#include "stdafx.h"
#include "Player.h"


Player::Player(Renderer * renderer) : Object(renderer)
{
	SetGraphic(IDLE_IMAGE);
	width = 1;
	height = 1;

}


Player::~Player()
{
}

void Player::InitPhysics()
{

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(TOMETER(position.x), TOMETER(position.y));
	body = PhysicsComponent::world.CreateBody(&bodyDef);


	dynamicBox.SetAsBox(TOMETER(width) / 2, TOMETER(height) / 2);



	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);

}

void Player::Draw()
{
	Vector3D pixelpos;
	position = body->GetPosition();
	position.Print();
	position.ToPixel(pixelpos);
	pixelpos.Print();
	//renderer->DrawSolidRect(pixelpos, TOPIXEL(width)*TOPIXEL(height), color, 0.1);
	renderer->DrawTexturedRectSeq(pixelpos, TOPIXEL(width*height), color, renderer->GetTexture(currentImageName.c_str()), ((int)animationTime) % maxAnimationX, 0, maxAnimationX, maxAnimationY,0.1);
}

void Player::Update()
{
	animationTime += UPDATE_FREQUENCY*5;

	position.x += dir.x*velocity.x*UPDATE_FREQUENCY;
	position.y += dir.y*velocity.y*UPDATE_FREQUENCY;
	position.z += dir.y*velocity.y*UPDATE_FREQUENCY;
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


