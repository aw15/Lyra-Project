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

void Keyboard(unsigned char key, int x, int y)
{

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
	meshMap["Line"]->CreateMeshByVertices({ {0,0,0},{1,1,1} }, { { 0,1,1 }, { 0,1,1 } });


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

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	glDisable(GL_CULL_FACE);

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
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
	glm::vec3 start = { 5,5,0 };
	glm::vec3 end =   {-5,-5,0 };
	unsigned int location = glGetUniformLocation(renderer->shaderProgramMap["line"], "startPosition");
	glUniform3fv(location, 1, glm::value_ptr(start));
	location = glGetUniformLocation(renderer->shaderProgramMap["line"], "endPosition");
	glUniform3fv(location, 1, glm::value_ptr(end));

	lineObject.Update( diff.count());
	lineObject.Render(renderer->shaderProgramMap["line"]);


	if (shapeSpawnTime > 2.0) { //2초마다 객체 생성


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
		shapeSpawnTime = 0.0f;
	}


	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기 
{
	glViewport(0, 0, w, h);
}

