#include "stdafx.h"
#include "Player.h"


Player::Player(Renderer * renderer) : Object(renderer)
{
	

	width = 1.7;
	height = 1.7;
	speed = { 1.f,1.f,0 };
	maxAnimationX = 1;
	maxAnimationY = 1;
	animationTime = 0.0f;
	hp = 100;//체력 설정
	playerState = PlayerState::IDLE;
	SetGraphic(IDLE_IMAGE);
}


Player::~Player()
{

}

void Player::InitPhysics()
{
	InitialValuePhysics physicsData;
	physicsData.height = height;
	physicsData.width = width;
	physicsData.groupIndex = PLAYER_GROUP;
	physicsData.position = position;
	physicsData.object = this;
	physics = new PhysicsComponent(physicsData);
}

void Player::Draw()
{
	Vector3D pixelpos;
	physics->GetPosition(pixelpos);
	pixelpos.ToPixel();

	renderer->DrawTexturedRectSeqXY(pixelpos, TOPIXEL(width), TOPIXEL(height), color, renderer->GetTexture(currentImageName.c_str()), ((int)animationTime) % maxAnimationX, 0, maxAnimationX, maxAnimationY,0.1);
}

void Player::Update()
{
	animationTime += UPDATE_FREQUENCY*5;
	physics->Update(dir, speed);
}

void Player::HandleInput(const char key, KeyStatus status)
{
	Command* command = inputHandler.HandleInput(key,status);

	if (command)
		command->Execute(*this);
}

void Player::Move(const Vector3D & dir)
{

	if (playerState != PlayerState::AIRATTACK)
	{
		this->dir.x = dir.x;
		this->dir.y = dir.y;


		auto vel = physics->body->GetLinearVelocity();
		if (vel.x > 1.f)
			vel.x = 1.f;
		else if (vel.x < -1.f)
			vel.x = -1.f;
		physics->body->SetLinearVelocity(vel);

		SetGraphic(RUN_IMAGE);
	}
}

void Player::Idle()
{
	playerState = PlayerState::IDLE;
	dir.x = 0;
	dir.y= 0;
	SetGraphic(IDLE_IMAGE);
}

void Player::AirAttack()
{
	if (playerState != PlayerState::RUN)
	{
		playerState = PlayerState::AIRATTACK;
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

void Player::BeginContact(b2Fixture* otherObjectFixture)
{
	Object* contactObject =static_cast<Object*>(otherObjectFixture->GetUserData());
	if(contactObject)
		cout << contactObject->GetHp() << endl;

}

void Player::EndContact(b2Fixture* otherObjectFixture)
{
}

void Player::PreSolve(b2Fixture* otherObjectFixture, const b2Manifold * oldManifold)
{

}

void Player::PostSolve(b2Fixture* otherObjectFixture, const b2ContactImpulse * impulse)
{
}


