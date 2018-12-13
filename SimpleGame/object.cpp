#include "stdafx.h"
#include "object.h"







Object::~Object()
{
}



void Object::Move(const Vector3D& dir)
{
	position.x += dir.x;
	position.y += dir.y;
}

void Object::Fire()
{
}

void Object::Update(float eTime)
{
	

}

void Object::Draw(Renderer* renderer)
{
	renderer->DrawSolidRect(position.x, position.y, position.z, 10.0f, 1.f, 0.f, 0.f, 1.f, 0.1f);
}





