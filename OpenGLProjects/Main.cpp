#include"stdafx.h"
#include"Renderer.h"
#include "BasicObject.h"

#define SPHERE_INDEX 0
#define CONE_INDEX 1
#define CYLINDER_INDEX 2

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

Renderer* renderer;
vector<BasicObject*> objectList;
auto prevTime = chrono::high_resolution_clock::now();

int CurrentShape = 0;


void Keyboard(unsigned char key, int x, int y)
{
	case key = ''
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

	auto tempObject = new BasicObject();
	BasicObjectDesc objDesc;
	objDesc.basicType = BasicShapeType::SPHERE;
	objDesc.primitiveType = GLU_LINE;
	tempObject->Initialize(objDesc, renderer, { 0,0,0}, { 0,0,0 }, {0.1,0.1,0.1});
	objectList.push_back(tempObject);

	tempObject = new BasicObject();
	objDesc;
	objDesc.basicType = BasicShapeType::CONE;
	objDesc.primitiveType = GLU_LINE;
	tempObject->Initialize(objDesc, renderer, { 0,0,0 }, { 0,0,0 }, { 1,1,1 });
	objectList.push_back(tempObject);

	tempObject = new BasicObject();
	objDesc;
	objDesc.basicType = BasicShapeType::CYLINDER;
	objDesc.primitiveType = GLU_LINE;
	tempObject->Initialize(objDesc, renderer, { 0,0,0 }, { 0,0,0 }, { 1,1,1 });
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
	glutMainLoop(); // 이벤트 처리 시작 

	return true;
}

GLUquadricObj* qobj = gluNewQuadric();

GLvoid drawScene() // 콜백 함수: 출력 
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 기본 흰색
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glUseProgram(renderer->ShaderProgramID);

	std::chrono::duration<double> diff = chrono::high_resolution_clock::now() - prevTime;
	prevTime = chrono::high_resolution_clock::now();

	for (auto& data : objectList)
	{
		data->Update(diff.count());
		data->Render();
	}

	
	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기 
{
	glViewport(0, 0, w, h);
}

