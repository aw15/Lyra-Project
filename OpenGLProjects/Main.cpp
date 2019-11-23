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

	case 'f': //도형그리기모드변경
		if (isPolygonMode == false) {
			glPolygonMode(GL_FRONT, GL_LINE);
			isPolygonMode = true;
		}
		else {
			glPolygonMode(GL_FRONT, GL_FILL);
			isPolygonMode = false;
		}
		break;
		//날라오는 경로 출력	


	case '+'://날라오는속도 증가.
		speedX = speedX + 0.5;
		speedY = speedY + 0.5;
		break;

	case '-': // 속도 감소
		speedX = speedX - 0.5;
		speedY = speedY - 0.5;
		break;

	case 'q': // 종료
		glutDestroyWindow(window);
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
	//서더랜드 알고리즘 테스트////////////////////////////////////////////////////////////////////////////
	float poly_size = 3;
	vector<glm::vec2> poly_points = { {100,150}, {200,250},
							  {300,200} };

	// Defining clipper polygon vertices in clockwise order 
	// 1st Example with square clipper 
	float clipper_size = 4;
	vector<glm::vec2> clipper_points= { {150,0}, {150,1000},
							  {1200,1200}, {1200,0} };

	suthHodgClip(poly_points, poly_size, clipper_points,
		clipper_size);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////


	////CyrusBeck 알고리즘///////////////////////////////////////////////////////////////////////////////////
	//glm::vec2 vertices[]
	//	= { {200, 50},
	//		{250, 100},
	//		{220, 30} };

	//// Make sure that the vertices 
	//// are put in a clockwise order 
	//int n = sizeof(vertices) / sizeof(vertices[0]);
	//glm::vec2 line[] = { {10, 10} , {200, 200} };

	//vector<glm::vec2> result;
	//auto r = CyrusBeck(vertices, line, n, result);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////


	InitDesc desc;
	desc.width = WIDTH;
	desc.height = HEIGHT;


	renderer = new Renderer{ desc };
	renderer->AddShader("vertex.glsl", "pixel.glsl", "basic");
	renderer->AddShader("lineVertex.glsl", "pixel.glsl", "line");

	renderer->SetViewMatrix({ 0,0,5 }, { 0,0,0 }, { 0,1,0 });
	renderer->SetProjMatrix(90.f, 0.0f, 1.0f);

	meshMap["Cube"] = new Mesh();
	meshMap["Pyramid"] = new Mesh();
	meshMap["Triangle"] = new Mesh();
	meshMap["Rectangle"] = new Mesh();
	meshMap["Line"] = new Mesh();

	meshMap["Cube"]->CreateCube();
	meshMap["Pyramid"]->CreatePyramid();
	meshMap["Triangle"]->CreateTriangle();
	meshMap["Rectangle"]->CreateRectangle();
	meshMap["Line"]->CreateMeshByVertices({ {0,0,0}, {1,1,1} }, { { 0,1,1 }, { 0,1,1 } });


	BasicObjectDesc objDesc;
	objDesc.primitiveType = GL_LINES;

	lineObject.Initialize(objDesc, renderer, meshMap["Line"]);
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

		cout << ox << " " << oy << endl;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		isLineComplete = false;
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

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	glDisable(GL_CULL_FACE);

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
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glUseProgram(renderer->shaderProgramMap["basic"]);


	std::chrono::duration<double> diff = chrono::high_resolution_clock::now() - prevTime;
	prevTime = chrono::high_resolution_clock::now();


	static float shapeSpawnTime = 2.0f;

	shapeSpawnTime += diff.count();

	for (auto& data : objectList)
	{
		data->Update( diff.count());
		data->Render(renderer->shaderProgramMap["basic"]);
	}

	glUseProgram(renderer->shaderProgramMap["line"]);
	if (isLineComplete == true) {
		glm::vec3 start = { mouseStartX,mouseStartY,0 };
		glm::vec3 end = { mouseEndX,mouseEndY,0 };

		unsigned int location = glGetUniformLocation(renderer->shaderProgramMap["line"], "startPosition");
		glUniform3fv(location, 1, glm::value_ptr(start));
		location = glGetUniformLocation(renderer->shaderProgramMap["line"], "endPosition");
		glUniform3fv(location, 1, glm::value_ptr(end));

		lineObject.Update(diff.count());
		lineObject.Render(renderer->shaderProgramMap["line"]);
	}


	if (shapeSpawnTime > 2.0) { //2초마다 객체 생성


		auto tempObject = new MeshObject();
		BasicObjectDesc objDesc;
		objDesc.primitiveType = GL_TRIANGLES;
		string meshName;
		if (rand() % 10 > 4)
			meshName = "Triangle";
		else
			meshName = "Rectangle";

		//랜덤하게 객체생성
		if (rand()%10 > 4) {
			tempObject->Initialize(objDesc, renderer, meshMap[meshName], { -5,0,0 }, { 0,0,0 }, { 1.0+rand()%3,1.0 + rand() % 3,1.0 + rand() % 3 }, { speedX,speedY,0 });
		}
		else {
			tempObject->Initialize(objDesc, renderer, meshMap[meshName], { 5,0,0 }, { 0,0,0 }, { 1.0 + rand() % 3,1.0 + rand() % 3,1.0 + rand() % 3 }, { -speedX,speedY,0 });

		}
		objectList.push_back(tempObject);
		shapeSpawnTime = 0.0f;
	}


	
	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기 
{
	glViewport(0, 0, w, h);
}


