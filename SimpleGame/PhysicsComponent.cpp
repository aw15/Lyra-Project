#include "stdafx.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(const Vector3D& position, const float width, const float height)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(TOMETER(position.x), TOMETER(position.y));
	body = PhysicsEngine::world.CreateBody(&bodyDef);
	dynamicBox.SetAsBox(TOMETER(width) / 2, TOMETER(height) / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.filter.groupIndex = PLAYER_GROUP;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->ResetMassData();//설정한 Density에 맞게 mass 조정
	fixture = body->CreateFixture(&fixtureDef);
}


PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update(const Vector3D & dir,const Vector3D& speed)
{

	b2Vec2 force;
	force.x = dir.x*speed.x*UPDATE_FREQUENCY;
	force.y = dir.y*speed.y*UPDATE_FREQUENCY;
	body->ApplyForce(force, body->GetWorldCenter(), true);

	auto vel = body->GetLinearVelocity();
	if (vel.x > 0.1f)
		vel.x = 0.1f;
	else if(vel.x< -0.1f)
		vel.x = -0.1f;
	body->SetLinearVelocity(vel);

}


