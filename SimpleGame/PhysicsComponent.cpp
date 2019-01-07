#include "stdafx.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(const InitialValuePhysics& data)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(data.position.x, data.position.y);

	body = PhysicsEngine::world.CreateBody(&bodyDef);
	dynamicBox.SetAsBox(data.width/2, data.height/2);
	float area = (data.width * 2)*(data.height * 2)*100;//100 for tranlating m to cm;

	b2FixtureDef fixtureDef;
	fixtureDef.filter.groupIndex = data.groupIndex;
	fixtureDef.shape = &dynamicBox;
	float mass = body->GetMass();
	fixtureDef.density = mass/ area;
	fixtureDef.friction = FRICTION;

	body->ResetMassData();//설정한 Density에 맞게 mass 조정

	//b2MassData mass;
	//body->GetMassData(&mass);
	//mass.mass = 1;
	//body->SetMassData(&mass);


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
	if (vel.x > 1.f)
		vel.x = 1.f;
	else if(vel.x< -1.f)
		vel.x = -1.f;
	body->SetLinearVelocity(vel);

}


