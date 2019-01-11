#include "stdafx.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(const InitialValuePhysics& data)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(data.position.x, data.position.y);//충돌체의 위치 초기화

	body = PhysicsEngine::world.CreateBody(&bodyDef);
	dynamicBox.SetAsBox(data.width/2, data.height/2);//박스형 충돌체 만들기
	float area = (data.width * 2)*(data.height * 2)*100;//100 for tranlating m to cm;

	b2FixtureDef fixtureDef;
	fixtureDef.filter.groupIndex = data.groupIndex;//그룹 설정
	fixtureDef.shape = &dynamicBox;//충돌체 설정
	float mass = body->GetMass();
	fixtureDef.density = mass/ area;//밀도를 무게/부피를 통해 구함
	fixtureDef.friction = FRICTION;//기본 마찰력 계수
	fixtureDef.userData = static_cast<void*>(data.object);

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
}


