#include "stdafx.h"
#include "MeshObject.h"
#include"Renderer.h"
#include"Mesh.h"

MeshObject::MeshObject()
{
}


MeshObject::~MeshObject()
{
}

bool MeshObject::Initialize(const BasicObjectDesc& desc, Renderer* renderer, Mesh* mesh)
{
	primitiveType = desc.primitiveType;
	basicType = desc.basicType;
	this->renderer = renderer;
	this->mesh = mesh;
	return true;
}

bool MeshObject::Initialize(const BasicObjectDesc & desc, Renderer * renderer, Mesh * mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	Initialize(desc, renderer, mesh);
	this->position = glm::translate(this->position, position);
	this->rotation = this->rotation * glm::rotate(this->rotation, glm::radians(rotation.x), { 1,0,0 });
	this->rotation = this->rotation * glm::rotate(this->rotation, glm::radians(rotation.y), { 0,1,0 });
	this->rotation = this->rotation * glm::rotate(this->rotation, glm::radians(rotation.z), { 0,0,1 });
	this->scale = glm::scale(this->scale, scale);
	return true;
}

bool MeshObject::Initialize(const BasicObjectDesc & desc, Renderer * renderer, Mesh* mesh , glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,glm::vec3 movementSpeed)
{
	Initialize(desc, renderer, mesh, position, rotation, scale);
	this ->movementSpeed = glm::vec3(movementSpeed.x, movementSpeed.y, movementSpeed.z);
	return true;
}

void MeshObject::Render(const GLuint shaderID)
{

	unsigned int modelLocation = glGetUniformLocation(shaderID, "u_transform");  //---버텍스세이더에서모델변환위치가져오기 
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMatrix));
	if (mesh)
	{
		renderer->DrawMeshObject(primitiveType, mesh->GetVAO(), mesh->size);
	}
}

void MeshObject::Update( const float elapsedTime)
{
	//finalMatrix = renderer->projMatrix * renderer->viewMatrix *  GetFinalMatrix();
	Translate(movementSpeed * (float)elapsedTime);
	Roll(rotationSpeed.x* elapsedTime);
	Pitch(rotationSpeed.y * elapsedTime);
	Yaw(rotationSpeed.z * elapsedTime);

	finalMatrix =   GetFinalMatrix();

}


