
#include "stdafx.h"
#include "object.h"







Object::Object(Renderer * renderer)
{
	this->renderer = renderer;
}

Object::~Object()
{
}


void Object::Move(const Vector3D& dir)
{
	this->dir.x = dir.x;
	this->dir.y = dir.y;
}

void Object::Idle()
{
	dir.x = 0;
	dir.y = 0;
}

void Object::Fire()
{
}

void Object::AirAttack()
{
}

//void Object::Update(float eTime)
//{
//	position.x += dir.x*velocity.x*eTime;
//	position.y += dir.y*velocity.y*eTime;
//	position.z += dir.y*velocity.y*eTime;
//}
//
//void Object::Draw()
//{
//	renderer->DrawSolidRect(position.x, position.y, position.z, 10.0f, 1.f, 0.f, 0.f, 1.f, 0.1f);
//}





