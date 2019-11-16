#include"stdafx.h"
#include"Renderer.h"
#include "BasicObject.h"
#include"MeshObject.h"
#include"Mesh.h"

#define LEFT_INDEX 0
#define RIGHT_INDEX 1

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

Renderer* renderer;
vector<MeshObject*> objectList;
unordered_map<string,Mesh*> meshMap;


auto prevTime = chrono::high_resolution_clock::now();

int g_currentShape = LEFT_INDEX;

int g_drawType = GLU_LINE;

bool isRevoling = false;

void Keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'x':
		objectList[LEFT_INDEX]->SetMovementSpeed({ 0,1,0 });
		break;
	case 'X':
		objectList[LEFT_INDEX]->SetRotationSpeed({ -20,0,0 });
		break;
	case 'y':
		objectList[RIGHT_INDEX]->SetRotationSpeed({ 0,20,0 });
		break;
	case 'Y':
		objectList[RIGHT_INDEX]->SetRotationSpeed({ 0,-20,0 });
		break;
	case 's':
		objectList[LEFT_INDEX]->SetRotationSpeed({ 0,0,0 });
		objectList[RIGHT_INDEX]->SetRotationSpeed({ 0, 0,0 });
		break;
	case 'b':
		objectList[LEFT_INDEX]->SetRotationSpeed({ 0, 20,0 });
		objectList[RIGHT_INDEX]->SetRotationSpeed({ 0, 20, 0 });
		objectList[LEFT_INDEX]->Reset();
		objectList[RIGHT_INDEX]->Reset();
		isRevoling == false ? isRevoling = true : isRevoling = false;
		if (!isRevoling)
		{
			objectList[LEFT_INDEX]->SetRotationSpeed({ 0, 0,0 });
			objectList[RIGHT_INDEX]->SetRotationSpeed({ 0, 0, 0 });
		}
		break;
	case 'c':
		auto temp = objectList[LEFT_INDEX]->mesh;
		objectList[LEFT_INDEX]->mesh = objectList[RIGHT_INDEX]->mesh;
		objectList[RIGHT_INDEX]->mesh = temp;

	}

}


void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		//do something here
		break;
	case GLUT_KEY_DOWN:
		//do something here
		break;
	case GLUT_KEY_LEFT:
		//do something here
		break;
	case GLUT_KEY_RIGHT:
		//do something here
		break;
	}
}


void Initialize()
{
	InitDesc desc;
	desc.width = WIDTH;
	desc.height = HEIGHT;
	desc.vertexShaderPath = "vertex.glsl";
	desc.pixelShaderPath = "pixel.glsl";
	renderer = new Renderer{ desc };
	renderer->Initialize();
	renderer->SetViewMatrix({ 0,0,5 }, { 0,0,0 }, { 0,1,0 });
	renderer->SetProjMatrix(90.f, 0.0f, 1.0f);

	meshMap["Cube"] = new Mesh();
	meshMap["Pyramid"] = new Mesh();
	meshMap["Triangle"] = new Mesh();
	meshMap["Rectangle"] = new Mesh();

	meshMap["Cube"]->CreateCube();
	meshMap["Pyramid"]->CreatePyramid();
	meshMap["Triangle"]->CreateTriangle();
	meshMap["Rectangle"]->CreateRectangle();

	/*auto tempObject = new MeshObject();
	BasicObjectDesc objDesc;
	objDesc.primitiveType = GL_TRIANGLES;
	tempObject->Initialize(objDesc, renderer, meshMap["Triangle"], { -5,0,0 }, { 0,0,0 }, { 2.5,2.5,2.5 }, {1,1,0});
	*//*objectList.push_back(tempObject);*/

	//tempObject = new MeshObject();
	//objDesc.primitiveType = GL_TRIANGLES;
	//tempObject->Initialize(objDesc, renderer, meshMap["Rectangle"], { 0.8,0,0 }, { 0,0,0 }, { 2.5,2.5,2.5 }, {-1,-1,0});
	//objectList.push_back(tempObject);
}

int main(int argc, char** argv) // ������ ����ϰ� �ݹ��Լ� ���� 
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
	glutSpecialFunc(SpecialInput);
	glutMainLoop(); // �̺�Ʈ ó�� ���� 

	return true;
}

GLUquadricObj* qobj = gluNewQuadric();

GLvoid drawScene() // �ݹ� �Լ�: ��� 
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �⺻ ���
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	glUseProgram(renderer->ShaderProgramID);
	glDisable(GL_CULL_FACE);

	std::chrono::duration<double> diff = chrono::high_resolution_clock::now() - prevTime;
	prevTime = chrono::high_resolution_clock::now();

	//objectList[LEFT_INDEX]->Update(diff.count(),isRevoling);
	//objectList[LEFT_INDEX]->Render();
	//	
	//objectList[RIGHT_INDEX]->Update(diff.count(), isRevoling);
	//objectList[RIGHT_INDEX]->Render();

	static float timeAccumulator = 0.0f;
	timeAccumulator += diff.count();
	for (auto& data : objectList)
	{
		data->Update(diff.count());
		data->Render();
	}

	if (timeAccumulator > 2.0) { //2�ʸ��� ��ü ����
		auto tempObject = new MeshObject();
		BasicObjectDesc objDesc;
		objDesc.primitiveType = GL_TRIANGLES;
		string meshName;
		if (rand() % 10 > 4)
			meshName = "Triangle";
		else
			meshName = "Rectangle";


		if (rand()%10 > 4) {
			tempObject->Initialize(objDesc, renderer, meshMap[meshName], { -5,0,0 }, { 0,0,0 }, { 1.0+rand()%3,1.0 + rand() % 3,1.0 + rand() % 3 }, { 1,1,0 });
		}
		else {
			tempObject->Initialize(objDesc, renderer, meshMap[meshName], { 5,0,0 }, { 0,0,0 }, { 1.0 + rand() % 3,1.0 + rand() % 3,1.0 + rand() % 3 }, { -1,1,0 });

		}
		objectList.push_back(tempObject);
		timeAccumulator = 0.0f;
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) // �ݹ� �Լ�: �ٽ� �׸��� 
{
	glViewport(0, 0, w, h);
}

