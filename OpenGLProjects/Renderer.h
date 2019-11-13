#pragma once
#include "basic.h"

struct InitDesc
{
	string vertexShaderPath;
	string pixelShaderPath;
	float width;
	float height;
};




class Renderer
{
public:
	Renderer(InitDesc initDesc);
	bool Initialize();
	void SetViewMatrix(const glm::vec3& cameraPosition, const glm::vec3& lookDir, const glm::vec3& cameraUp);
	void SetProjMatrix( float fov ,  float nearZ,  float farZ);
	~Renderer();



	void DrawPrimitiveObject(const int primitiveType, GLuint vao,const int count);
public:
	InitDesc initDesc;
	GLuint ShaderProgramID;

private:
	bool CompileShader();

	glm::mat4 viewMatrix = glm::mat4{};
	glm::mat4 projMatrix = glm::mat4{};
};

