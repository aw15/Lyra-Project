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
auto prevTime = chrono::high_resolution_clock::now();

int g_currentShape = LEFT_INDEX;
int g_drawType = GLU_LINE;


auto cubeMesh = new Mesh();
auto pyramidMesh = new Mesh();

bool isRevoling = false;

void Keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'x':
		objectList[LEFT_INDEX]->SetRotationSpeed({ 20,0,0 });
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
	renderer->SetViewMatrix({ 0,0,-10 }, { 0,0,0 }, { 0,1,0 });
	renderer->SetProjMatrix(90.f, 0.0f, 1.0f);

	cubeMesh->CreateCube();
	pyramidMesh->CreatePyramid();

	auto tempObject = new MeshObject();
	BasicObjectDesc objDesc;
	objDesc.primitiveType = GL_TRIANGLES;
	tempObject->Initialize(objDesc, renderer, cubeMesh, { -0.8,0,0 }, { 0,0,0 }, { 0.1,0.1,0.1 });
	objectList.push_back(tempObject);

	tempObject = new MeshObject();
	objDesc.primitiveType = GL_TRIANGLES;
	tempObject->Initialize(objDesc, renderer, pyramidMesh, { 0.8,0,0 }, { 0,0,0 }, { 0.1,0.1,0.1 });
	objectList.push_back(tempObject);
}

int main(int argc, char** argv) // 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(WIDTH, HEIGHT); // 윈도우의 크기 지정
	auto window = glutCreateWindow("Example1"); // 윈도우 생성(윈도우 이름)

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	Initialize();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialInput);
	glutMainLoop(); // 이벤트 처리 시작 



	return true;
}

GLUquadricObj* qobj = gluNewQuadric();

GLvoid drawScene() // 콜백 함수: 출력 
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 기본 흰색
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glUseProgram(renderer->ShaderProgramID);
	glDisable(GL_CULL_FACE);

	std::chrono::duration<double> diff = chrono::high_resolution_clock::now() - prevTime;
	prevTime = chrono::high_resolution_clock::now();

	objectList[LEFT_INDEX]->Update(diff.count(),isRevoling);
	objectList[LEFT_INDEX]->Render();
		
	objectList[RIGHT_INDEX]->Update(diff.count(), isRevoling);
	objectList[RIGHT_INDEX]->Render();

	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기 
{
	glViewport(0, 0, w, h);
}

