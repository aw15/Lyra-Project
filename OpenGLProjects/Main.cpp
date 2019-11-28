#include"stdafx.h"
#include"Renderer.h"
#include"MeshObject.h"
#include"Mesh.h"
#include"Physics.h"

#define LEFT_INDEX 0
#define RIGHT_INDEX 1

#define TOP_DOWN 0b1100
#define LEFT_RIGHT 0b0011

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

Renderer* renderer;
Physics physics;
vector<MeshObject*> objectList;
vector<Mesh*> meshes;

MeshObject lineObject;

unordered_map<string,Mesh*> meshMap;


auto prevTime = chrono::high_resolution_clock::now();

int g_currentShape = LEFT_INDEX;

int g_drawType = GLU_LINE;

bool isRevoling = false;

float mouseStartX, mouseStartY, mouseEndX, mouseEndY;

bool isPolygonMode = false;
int window;
float speedX = 1;
float speedY = 1;
bool isLineComplete = false;

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		break;
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


	renderer = new Renderer{ desc };
	renderer->AddShaderWithTwoParam("vertex.glsl", "pixel.glsl", "basic");
	renderer->AddShaderWithTwoParam("lineVertex.glsl", "pixel.glsl", "line");
	renderer->AddShaderWithTwoParam("vertexBasic.glsl", "pixel.glsl","obj");

	renderer->SetViewMatrix({ 0,0,5 }, { 0,0,0 }, { 0,1,0 });
	renderer->SetProjMatrix(90.f, 0.0f, 1.0f);

	meshMap["Cube"] = new Mesh();
	meshMap["Cube"]->CreateMeshByObj("Mesh/cube.obj");


	auto tempObject = new MeshObject();
	BasicObjectDesc objDesc;
	objDesc.primitiveType = GL_TRIANGLES;

	tempObject->Initialize(objDesc, renderer, meshMap["Cube"], { 0,0,0.5 }, { 0,0,0 }, { 1,1,1});
	//tempObject->SetRotationSpeed({ 3,0,0 });
	objectList.push_back(tempObject);

}


void CleanUp()
{
	for (auto& data : objectList)
	{
		delete data;
	}

	for (auto iter = meshMap.begin(); iter != meshMap.end(); iter++)
	{
		(*iter).second->Delete();
		delete (*iter).second;
	}

	delete renderer;

}

void MousDrag(int x,int y) {
	float ox;
	float oy;
	isLineComplete = true;
	convertDeviceXYOpneglXY(x, y, &ox, &oy);

	mouseEndX = ox;
	mouseEndY = oy;
}


void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//좌표계변환
		float ox;
		float oy;
		convertDeviceXYOpneglXY(x, y, &ox, &oy);		
		mouseStartX = ox;
		mouseStartY = oy;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		

	}
}



int main(int argc, char** argv) // 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(WIDTH, HEIGHT); // 윈도우의 크기 지정
	window = glutCreateWindow("Example1"); // 윈도우 생성(윈도우 이름)

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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MousDrag);
	glutSpecialFunc(SpecialInput);
	glutMainLoop(); // 이벤트 처리 시작 

	CleanUp();//메모리 해제

	return true;
}


GLvoid drawScene() // 콜백 함수: 출력 
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 기본 흰색
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glUseProgram(renderer->shaderProgramMap["obj"]);


	std::chrono::duration<double> diff = chrono::high_resolution_clock::now() - prevTime;
	prevTime = chrono::high_resolution_clock::now();

	for(auto& data:objectList)
	{
		data->Update(diff.count());
		data->Render(renderer->shaderProgramMap["obj"]);
	}

	
	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기 
{
	glViewport(0, 0, w, h);
}


