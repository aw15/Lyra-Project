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

	//위쪽
	b2Vec2 a;
	b2Vec2 b;
	a.x = TOMETER(-WIDTH / 2.0f);
	a.y = TOMETER(-HEIGHT / 2.0f) + 0.3f;

	b.x = TOMETER(WIDTH / 2.0f);
	b.y = TOMETER(-HEIGHT / 2.0f) + 0.3f;
	groundEdge.Set(a,b);
	groundBody->CreateFixture(&boxShapeDef);

	//// 왼쪽

	//groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));

	//groundBody->CreateFixture(&boxShapeDef);



	//// 위쪽

	//groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO),

	//	b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));

	//groundBody->CreateFixture(&boxShapeDef);



	//// 오른쪽

	//groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO),

	//	b2Vec2(winSize.width / PTM_RATIO, 0));

	//groundBody->CreateFixture(&boxShapeDef);


}

void PhysicsEngine::Update()
{
	world.Step(UPDATE_FREQUENCY,velocityIterations, positionIterations);
}
