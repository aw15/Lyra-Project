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
	// VAO �������ϰ��Ҵ��ϱ� 
	glGenVertexArrays(1, &vao);
	// VAO�����ε��ϱ� 
	glBindVertexArray(vao);


	// 2���� VBO�������ϰ��Ҵ��ϱ� 
	glGenBuffers(2, vbo);
	//--- 1��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (��ǥ��)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// ���� diamond �������ؽ������Ͱ������ۿ������Ѵ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(objectInfo.mesh.vertex[0]) * objectInfo.mesh.vertex.size() , &objectInfo.mesh.vertex[0], GL_STATIC_DRAW);
	// ��ǥ���� attribute �ε��� 0��������Ѵ�: ���ؽ��� 3* float 
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 0������밡���ϰ��� 
	glEnableVertexAttribArray(0);

	//---2��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (����)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// ���� colors�������ؽ������������Ѵ�. 
	// colors �迭�ǻ�����: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, sizeof(objectInfo.mesh.color[0]) *objectInfo.mesh.color.size(), &objectInfo.mesh.color[0], GL_STATIC_DRAW);
	// ������ attribute �ε��� 1��������Ѵ�: ���ؽ���3*float 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 1������밡���ϰ���. 
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
