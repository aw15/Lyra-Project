#pragma once
class PhysicsComponent
{
public:
	PhysicsComponent(const InitialValuePhysics& data);
	~PhysicsComponent();
	void GetPosition(Vector3D& param) { param = body->GetPosition(); }

	void Update(const Vector3D& dir,const Vector3D& speed);
	b2PolygonShape dynamicBox;
	b2CircleShape circleShape;
	b2Body* body;
	b2Fixture* fixture;
};

