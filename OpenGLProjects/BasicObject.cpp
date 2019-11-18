#include "stdafx.h"
#include "BasicObject.h"
#include"Renderer.h"

BasicObject::BasicObject()
{

}


BasicObject::~BasicObject()
{
}

bool BasicObject::Initialize(const BasicObjectDesc& desc, Renderer* renderer)
{
	primitiveType = desc.primitiveType;
	basicType = desc.basicType;
	this->renderer = renderer;
	return true;
}

bool BasicObject::Initialize(const BasicObjectDesc & desc, Renderer * renderer, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	Initialize(desc, renderer);
	this->position = glm::translate(this->position, position);
	this->rotation = this->rotation * glm::rotate(this->rotation, glm::radians(rotation.x), {1,0,0});
	this->rotation = this->rotation * glm::rotate(this->rotation, glm::radians(rotation.y), { 0,1,0 });
	this->rotation = this->rotation * glm::rotate(this->rotation, glm::radians(rotation.z), { 0,0,1 });
	this->scale = glm::scale(this->scale,scale);

	return true;
}

void BasicObject::Render()
{

//	renderer->DrawBasicObject(basicType, primitiveType);
}

void BasicObject::Update(const double elapsedTime)
{
	//finalMatrix = renderer->projMatrix * renderer->viewMatrix *  GetFinalMatrix();
	finalMatrix = GetFinalMatrix();
	//unsigned int modelLocation = glGetUniformLocation(renderer->ShaderProgramID, "u_transform");  //---버텍스세이더에서모델변환위치가져오기 
//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMatrix));
}

glm::mat4 BasicObject::GetFinalMatrix()
{
	return position*rotation*scale;
}

void BasicObject::Roll(float angle)
{
	rotation = glm::rotate(rotation, glm::radians(angle), { 0,1,0 });
}

void BasicObject::Pitch(float angle)
{
	rotation = glm::rotate(rotation, glm::radians(angle), { 1,0,0 });
}

void BasicObject::Yaw(float angle)
{
	rotation = glm::rotate(rotation, glm::radians(angle), { 0,0,1 });
}

void BasicObject::Translate(glm::vec3 amount)
{
	position = glm::translate(position, amount);
}
