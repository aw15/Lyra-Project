#include "stdafx.h"
#include "Slime.h"




Slime::Slime(Renderer * renderer) : Object(renderer)
{

	width = 1;
	height = 1;
	speed = { 0.1f,0.1f,0 };
	maxAnimationX = 1;
	maxAnimationY = 1;
	animationTime = 0.0f;
	slimeState = AIState::IDLE;
	SetGraphic(IDLE_IMAGE);
}


Slime::~Slime()
{
}

void Slime::InitPhysics()
{

	physics = new PhysicsComponent(position, width, height);
}

void Slime::Draw()
{
	Vector3D pixelpos;
	physics->GetPosition(pixelpos);
	pixelpos.ToPixel();

	renderer->DrawTexturedRectSeq(pixelpos, TOPIXEL(width*height), color, renderer->GetTexture(currentImageName.c_str()), ((int)animationTime) % maxAnimationX, 0, maxAnimationX, maxAnimationY, 0.1);
}

void Slime::Update()
{
	animationTime += UPDATE_FREQUENCY * 5;
	physics->Update(dir, speed);
}

void Slime::HandleAI(const AIState state)
{
	Command* command = inputHandler.HandleAI(state);
	
	if (command)
		command->Execute(*this);
}

void Slime::Move(const Vector3D & dir)
{
	this->dir.x = dir.x;
	this->dir.y = dir.y;

	SetGraphic(IDLE_IMAGE);
}

void Slime::Idle()
{
	slimeState = AIState::IDLE;
	dir.x = 0;
	dir.y = 0;
	SetGraphic(IDLE_IMAGE);
}



void Slime::SetGraphic(const unsigned int image)
{
	switch (image)
	{
	case IDLE_IMAGE:
		currentImageName = "slime_idle";
		maxAnimationX = 8;
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
