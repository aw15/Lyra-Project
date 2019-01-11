#include "stdafx.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(const InitialValuePhysics& data)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(data.position.x, data.position.y);//�浹ü�� ��ġ �ʱ�ȭ

	body = PhysicsEngine::world.CreateBody(&bodyDef);
	dynamicBox.SetAsBox(data.width/2, data.height/2);//�ڽ��� �浹ü �����
	float area = (data.width * 2)*(data.height * 2)*100;//100 for tranlating m to cm;

	b2FixtureDef fixtureDef;
	fixtureDef.filter.groupIndex = data.groupIndex;//�׷� ����
	fixtureDef.shape = &dynamicBox;//�浹ü ����
	float mass = body->GetMass();
	fixtureDef.density = mass/ area;//�е��� ����/���Ǹ� ���� ����
	fixtureDef.friction = FRICTION;//�⺻ ������ ���
	fixtureDef.userData = static_cast<void*>(data.object);

	body->ResetMassData();//������ Density�� �°� mass ����

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
}


