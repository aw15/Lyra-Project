#include "stdafx.h"
#include "Mesh.h"
#include"Renderer.h"



void Mesh::Render(Renderer* const renderer)
{
	if (type == MeshType::Obj)
	{
		renderer->DrawMeshObject(GL_TRIANGLES, vao, vertices.size());
	}
}

void Mesh::CreateBasicObject(MeshType type)
{
	if (type == MeshType::Obj)
	{
		//// VAO �������ϰ��Ҵ��ϱ� 
		//glGenVertexArrays(1, &vao);
		//// VAO�����ε��ϱ� 
		//glBindVertexArray(vao);


		//// 2���� VBO�������ϰ��Ҵ��ϱ� 
		//glGenBuffers(2, vbo);
		////--- 1��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (��ǥ��)������ 
		//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

		//// ���� diamond �������ؽ������Ͱ������ۿ������Ѵ�.
		//glBufferData(GL_ARRAY_BUFFER, sizeof(objectInfo.mesh.vertex[0]) * objectInfo.mesh.vertex.size(), &objectInfo.mesh.vertex[0], GL_STATIC_DRAW);
		//// ��ǥ���� attribute �ε��� 0��������Ѵ�: ���ؽ��� 3* float 
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//// attribute �ε��� 0������밡���ϰ��� 
		//glEnableVertexAttribArray(0);

		////---2��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (����)������ 
		//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		//// ���� colors�������ؽ������������Ѵ�. 
		//// colors �迭�ǻ�����: 9 *float 
		//glBufferData(GL_ARRAY_BUFFER, sizeof(objectInfo.mesh.color[0]) *objectInfo.mesh.color.size(), &objectInfo.mesh.color[0], GL_STATIC_DRAW);
		//// ������ attribute �ε��� 1��������Ѵ�: ���ؽ���3*float 
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//// attribute �ε��� 1������밡���ϰ���. 
		//glEnableVertexAttribArray(1);
	}
}

void Mesh::CreateCube()
{
	vector<float> g_vertex_buffer_data = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};

	size = g_vertex_buffer_data.size()/3;



	GLfloat g_color_buffer_data[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
	};


	// VAO �������ϰ��Ҵ��ϱ� 
	glGenVertexArrays(1, &vao);
	// VAO�����ε��ϱ� 
	glBindVertexArray(vao);


	// 2���� VBO�������ϰ��Ҵ��ϱ� 
	glGenBuffers(2, vbo);
	//--- 1��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (��ǥ��)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// ���� diamond �������ؽ������Ͱ������ۿ������Ѵ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (size * 3) , &g_vertex_buffer_data[0], GL_STATIC_DRAW);
	// ��ǥ���� attribute �ε��� 0��������Ѵ�: ���ؽ��� 3* float 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 0������밡���ϰ��� 
	glEnableVertexAttribArray(0);

	//---2��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (����)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// ���� colors�������ؽ������������Ѵ�. 
	// colors �迭�ǻ�����: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data[0]) * 108, &g_color_buffer_data[0], GL_STATIC_DRAW);
	// ������ attribute �ε��� 1��������Ѵ�: ���ؽ���3*float 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 1������밡���ϰ���. 
	glEnableVertexAttribArray(1);

}

void Mesh::CreatePyramid()
{
	vector<float> g_vertex_buffer_data = {
		0,1,0,
		-1,-1,1,
		1,-1,1,
		0,1,0,
		-1,-1,1,
		0,-1,-1,
		0,1,0,
		0,-1,-1,
		1,-1,1,
		-1,-1,1,
		0,-1,-1,
		1,-1, 1
	};

	size = g_vertex_buffer_data.size() / 3;

	for (int i = 0; i < size; i += 3)
	{
		colors.push_back({ rand()/(float)RAND_MAX, rand() / (float)RAND_MAX, 1});
	}

	// VAO �������ϰ��Ҵ��ϱ� 
	glGenVertexArrays(1, &vao);
	// VAO�����ε��ϱ� 
	glBindVertexArray(vao);


	// 2���� VBO�������ϰ��Ҵ��ϱ� 
	glGenBuffers(2, vbo);
	//--- 1��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (��ǥ��)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// ���� diamond �������ؽ������Ͱ������ۿ������Ѵ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (size * 3), &g_vertex_buffer_data[0], GL_STATIC_DRAW);
	// ��ǥ���� attribute �ε��� 0��������Ѵ�: ���ؽ��� 3* float 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 0������밡���ϰ��� 
	glEnableVertexAttribArray(0);

	//---2��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (����)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// ���� colors�������ؽ������������Ѵ�. 
	// colors �迭�ǻ�����: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors[0]) * colors.size(), &colors[0], GL_STATIC_DRAW);
	// ������ attribute �ε��� 1��������Ѵ�: ���ؽ���3*float 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 1������밡���ϰ���. 
	glEnableVertexAttribArray(1);
}

void Mesh::CreateTriangle()
{

	vertices.push_back({ 0,0.5,0 });
	vertices.push_back({ -0.5,0,0 });
	vertices.push_back({ 0.5,0,0 });
	

	size = vertices.size();

	for (int i = 0; i < size; i += 3)
	{
		colors.push_back({ rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1 });
	}

	// VAO �������ϰ��Ҵ��ϱ� 
	glGenVertexArrays(1, &vao);
	// VAO�����ε��ϱ� 
	glBindVertexArray(vao);

	// 2���� VBO�������ϰ��Ҵ��ϱ� 
	glGenBuffers(2, vbo);
	//--- 1��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (��ǥ��)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// ���� diamond �������ؽ������Ͱ������ۿ������Ѵ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * (size), &vertices[0], GL_STATIC_DRAW);
	// ��ǥ���� attribute �ε��� 0��������Ѵ�: ���ؽ��� 3* float 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 0������밡���ϰ��� 
	glEnableVertexAttribArray(0);

	//---2��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (����)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// ���� colors�������ؽ������������Ѵ�. 
	// colors �迭�ǻ�����: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors[0]) * colors.size(), &colors[0], GL_STATIC_DRAW);
	// ������ attribute �ε��� 1��������Ѵ�: ���ؽ���3*float 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 1������밡���ϰ���. 
	glEnableVertexAttribArray(1);
}

void Mesh::CreateRectangle()
{

	vertices.push_back({ -0.5,0.5,0 });
	vertices.push_back({ -0.5,-0.5,0 });
	vertices.push_back({ 0.5,0.5,0 });
	vertices.push_back({ 0.5,0.5,0 });
	vertices.push_back({ -0.5,-0.5,0 });
	vertices.push_back({ 0.5,-0.5,0 });
	
	
	

	size = vertices.size();

	for (int i = 0; i < size; i += 1)
	{
		colors.push_back({ 1,0.5,0 });
	}

	// VAO �������ϰ��Ҵ��ϱ� 
	glGenVertexArrays(1, &vao);
	// VAO�����ε��ϱ� 
	glBindVertexArray(vao);

	// 2���� VBO�������ϰ��Ҵ��ϱ� 
	glGenBuffers(2, vbo);
	//--- 1��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (��ǥ��)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// ���� diamond �������ؽ������Ͱ������ۿ������Ѵ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * (size), &vertices[0], GL_STATIC_DRAW);
	// ��ǥ���� attribute �ε��� 0��������Ѵ�: ���ؽ��� 3* float 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 0������밡���ϰ��� 
	glEnableVertexAttribArray(0);

	//---2��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (����)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// ���� colors�������ؽ������������Ѵ�. 
	// colors �迭�ǻ�����: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors[0]) * colors.size(), &colors[0], GL_STATIC_DRAW);
	// ������ attribute �ε��� 1��������Ѵ�: ���ؽ���3*float 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 1������밡���ϰ���. 
	glEnableVertexAttribArray(1);
}

void Mesh::CreateMeshByVertices(const vector<glm::vec3>& vertices, const vector<glm::vec3>& colors)
{

	size = vertices.size();


	// VAO �������ϰ��Ҵ��ϱ� 
	glGenVertexArrays(1, &vao);
	// VAO�����ε��ϱ� 
	glBindVertexArray(vao);

	// 2���� VBO�������ϰ��Ҵ��ϱ� 
	glGenBuffers(2, vbo);
	//--- 1��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (��ǥ��)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// ���� diamond �������ؽ������Ͱ������ۿ������Ѵ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * (size), &vertices[0], GL_STATIC_DRAW);
	// ��ǥ���� attribute �ε��� 0��������Ѵ�: ���ؽ��� 3* float 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 0������밡���ϰ��� 
	glEnableVertexAttribArray(0);

	//---2��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (����)������ 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// ���� colors�������ؽ������������Ѵ�. 
	// colors �迭�ǻ�����: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors[0]) * colors.size(), &colors[0], GL_STATIC_DRAW);
	// ������ attribute �ε��� 1��������Ѵ�: ���ؽ���3*float 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 1������밡���ϰ���. 
	glEnableVertexAttribArray(1);
}

void Mesh::Delete()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(2, vbo);
}
