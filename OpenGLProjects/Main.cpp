#include"stdafx.h"
#include"Renderer.h"
#include "Object.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);


static const float cube_vertices[] = {
	/* front surface is blue */
	-0.5,  0.5, 0.5,
	-0.5, -0.5, 0.5,
	 0.5, -0.5, 0.5,
	 0.5,  0.5, 0.5,
	 /* left surface is green */
	 -0.5,  0.5,  0.5,
	 -0.5,  0.5, -0.5,
	 -0.5, -0.5, -0.5,
	 -0.5, -0.5,  0.5,
	 /* top surface is red */
	 -0.5, 0.5, 0.5,
	  0.5, 0.5, 0.5,
	  0.5, 0.5, -0.5,
	 -0.5, 0.5, -0.5,
	 /* right surface is yellow */
	  0.5,  0.5, -0.5,
	  0.5,  0.5,  0.5,
	  0.5, -0.5,  0.5,
	  0.5, -0.5, -0.5,
	  /* back surface is cyan */
	  -0.5,  0.5, -0.5,
	   0.5,  0.5, -0.5,
	   0.5, -0.5, -0.5,
	  -0.5, -0.5, -0.5,
	  /* bottom surface is magenta */
	  -0.5, -0.5, -0.5,
	  -0.5, -0.5,  0.5,
	   0.5, -0.5,  0.5,
	   0.5, -0.5, -0.5,
};


void Keyboard(unsigned char key, int x, int y)
{
	//switch (key) {

	//case 'f': //�����׸����庯��
	//	if (polygonMode == false) {
	//		glPolygonMode(GL_FRONT, GL_LINE);
	//		polygonMode = true;
	//	}
	//	else {
	//		glPolygonMode(GL_FRONT, GL_FILL);
	//		polygonMode = false;
	//	}
	//	break;

	//case 'm': //4���� �簢���� �ð�ݴ�������� �̵� (������ �������ʴ´�.)
	//	if (isMove != true) {

	//		isMove = true;
	//	}
	//	break;

	//case 's': // ���߱�
	//	isMove = false;
	//	break;

	//case 'c'://�簢���� ����ٲٱ�
	//	srand(time(NULL));
	//	colors[triangleIndex * 3] = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX, rand() / (float)RAND_MAX };
	//	colors[triangleIndex * 3 + 1] = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX, rand() / (float)RAND_MAX };
	//	colors[triangleIndex * 3 + 2] = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX, rand() / (float)RAND_MAX };

	//	triangleIndex += 1;
	//	triangleIndex %= 4;
	//	break;

	//case 'q':
	//	glutDestroyWindow(WIN);
	//	break;
	//}
}



Renderer* renderer;

vector<Object*> objectList;
ObjectDesc objDesc;

void Initialize()
{
	InitDesc desc;
	desc.height = WIDTH;
	desc.height = HEIGHT;
	desc.vertexShaderPath = "vertex.glsl";
	desc.pixelShaderPath = "pixel.glsl";
	renderer = new Renderer{ desc };
	renderer->Initialize();
	renderer->SetViewMatrix({ 0,0,-10 }, { 0,0,0 }, { 0,1,0 });
	renderer->SetProjMatrix(90.f, 0.0f, 1.0f);

	auto tempObject = new Object();

	objDesc.mesh.vertex.push_back({ 0, 0.5, 0 });
	objDesc.mesh.vertex.push_back({ -1, 0, 0 });
	objDesc.mesh.vertex.push_back({1, 0, 0});

	objDesc.mesh.color.push_back({ 1, 1, 0 });
	objDesc.mesh.color.push_back({ 1, 0, 0 });
	objDesc.mesh.color.push_back({ 1, 0, 0 });

	tempObject->Initialize(objDesc);

	objectList.push_back(tempObject);
}

void main(int argc, char** argv) // ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(WIDTH, HEIGHT); // �������� ũ�� ����
	auto window = glutCreateWindow("Example1"); // ������ ����(������ �̸�)

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	Initialize();


	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid drawScene() // �ݹ� �Լ�: ��� 
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �⺻ ���
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	glUseProgram(renderer->ShaderProgramID);

	//GLuint vao;
	//GLuint vbo[2];
	//// VAO �������ϰ��Ҵ��ϱ� 
	//glGenVertexArrays(1, &vao);
	//// VAO�����ε��ϱ� 
	//glBindVertexArray(vao);


	//// 2���� VBO�������ϰ��Ҵ��ϱ� 
	//glGenBuffers(2, vbo);
	////--- 1��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (��ǥ��)������ 
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//for (auto data : objDesc.mesh.vertex)
	//{
	//	cout << data.x << endl;
	//}

	//// ���� diamond �������ؽ������Ͱ������ۿ������Ѵ�.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* objDesc.mesh.vertex.size(), &objDesc.mesh.vertex[0], GL_STATIC_DRAW);
	//// ��ǥ���� attribute �ε��� 0��������Ѵ�: ���ؽ��� 3* float 
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//// attribute �ε��� 0������밡���ϰ��� 
	//glEnableVertexAttribArray(0);

	////---2��° VBO��Ȱ��ȭ�Ͽ����ε��ϰ�, ���ؽ��Ӽ� (����)������ 
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//// ���� colors�������ؽ������������Ѵ�. 
	//// colors �迭�ǻ�����: 9 *float 
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * objDesc.mesh.color.size() , &objDesc.mesh.color[0], GL_STATIC_DRAW);
	//// ������ attribute �ε��� 1��������Ѵ�: ���ؽ���3*float 
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//// attribute �ε��� 1������밡���ϰ���. 
	//glEnableVertexAttribArray(1);
	//glm::mat4 finalMatrix{};
	//glUniformMatrix4fv(glGetUniformLocation(renderer->ShaderProgramID, "transform"), 1, GL_FALSE, glm::value_ptr(finalMatrix));

	//glBindVertexArray(vao);
	//glPointSize(10.0f);
	//glDrawArrays(GL_POINTS, 0, 3);


	for (auto& const data : objectList)
	{
		data->Render(renderer);
	}

	
	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) // �ݹ� �Լ�: �ٽ� �׸��� 
{
	glViewport(0, 0, w, h);
}

