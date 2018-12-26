#pragma once
class PhysicsComponent
{
public:
	PhysicsComponent(const Vector3D& position,const float width,const float height);
	~PhysicsComponent();
	void GetPosition(Vector3D& param) { param = body->GetPosition(); }

	void Update(const Vector3D& dir,const Vector3D& speed);
	b2PolygonShape dynamicBox;
	b2Body* body;
	b2Fixture* fixture;
};

