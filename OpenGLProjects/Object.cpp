#include "stdafx.h"
#include "Object.h"
#include"Renderer.h"

Object::Object()
{

}


Object::~Object()
{
}

bool Object::Initialize(const ObjectDesc & object)
{
	objectInfo = object;
	// VAO 를지정하고할당하기 
	glGenVertexArrays(1, &vao);
	// VAO를바인드하기 
	glBindVertexArray(vao);


	// 2개의 VBO를지정하고할당하기 
	glGenBuffers(2, vbo);
	//--- 1번째 VBO를활성화하여바인드하고, 버텍스속성 (좌표값)을저장 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// 변수 diamond 에서버텍스데이터값을버퍼에복사한다.
	glBufferData(GL_ARRAY_BUFFER, sizeof(objectInfo.mesh.vertex[0]) * objectInfo.mesh.vertex.size() , &objectInfo.mesh.vertex[0], GL_STATIC_DRAW);
	// 좌표값을 attribute 인덱스 0번에명시한다: 버텍스당 3* float 
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute 인덱스 0번을사용가능하게함 
	glEnableVertexAttribArray(0);

	//---2번째 VBO를활성화하여바인드하고, 버텍스속성 (색상)을저장 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// 변수 colors에서버텍스색상을복사한다. 
	// colors 배열의사이즈: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, sizeof(objectInfo.mesh.color[0]) *objectInfo.mesh.color.size(), &objectInfo.mesh.color[0], GL_STATIC_DRAW);
	// 색상값을 attribute 인덱스 1번에명시한다: 버텍스당3*float 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute 인덱스 1번을사용가능하게함. 
	glEnableVertexAttribArray(1);


	return true;
}

void Object::Render(Renderer* const renderer)
{
	glUniformMatrix4fv(glGetUniformLocation(renderer->ShaderProgramID, "transform"), 1 ,GL_FALSE, glm::value_ptr(finalMatrix));
	glPointSize(10.0f);
	renderer->DrawPrimitiveObject(GL_TRIANGLES,vao, objectInfo.mesh.vertex.size());
}

glm::mat4 Object::GetFinalMatrix()
{
	return position*rotation*scale;
}
