#include "stdafx.h"
#include "PhysicsEngine.h"

b2Vec2 PhysicsEngine::gravity = { 0.0f, GRAVITY };
b2World PhysicsEngine::world{ gravity };


PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::Initialize()
{

	world.SetContinuousPhysics(true);
	world.SetAllowSleeping(true);


	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
	boxShapeDef.userData = nullptr;
	
	//À§ÂÊ
	b2Vec2 a;
	b2Vec2 b;
	a.x = TOMETER(-WIDTH / 2.0f);
	a.y = TOMETER(-HEIGHT / 2.0f);

	b.x = TOMETER(WIDTH / 2.0f);
	b.y = TOMETER(-HEIGHT / 2.0f);
	groundEdge.Set(a,b);
	groundBody->CreateFixture(&boxShapeDef);
}

void PhysicsEngine::Update()
{
	world.Step(UPDATE_FREQUENCY,velocityIterations, positionIterations);
}
