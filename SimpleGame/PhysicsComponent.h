#pragma once
class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	static void Initialize();
	static void Update();

public:
	static b2Vec2 gravity;
	static b2World world;
	const static int velocityIterations = 6;
	const static int positionIterations = 2;
};
