#include"stdafx.h"
#include"Renderer.h"
#include"MeshObject.h"
#include"Mesh.h"
#include"Physics.h"
#include "16번.h"

#define LEFT_INDEX 0
#define RIGHT_INDEX 1

#define TOP_DOWN 0b1100
#define LEFT_RIGHT 0b0011

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
int window;
Renderer* renderer;
Physics physics;
vector<MeshObject*> objectList;
vector<Mesh*> meshes;

MeshObject lineObject;

unordered_map<string,Mesh*> meshMap;

bool isRotateX = false;

auto prevTime = chrono::high_resolution_clock::now();

float mouseStartX, mouseStartY, mouseEndX, mouseEndY;

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'b': 
		// 아래몸체가 y축에대하여양/음방향으로회전한다 
		//아래몸체가회전하면중앙몸체와맨위의팔은같이회전한다

		for (int i = 1; i < 4; ++i) {
			objectList[i]->rotationSpeed.y = 10;
		}

		break;

	case 'm':
		//크레인의중앙몸체가 x축에대하여양/음방향으로회전한다. 
		//회전각도는90 ~ 180도사이로정하고, 중앙몸체가 회전하면 맨위의 팔도같이회전한다. 
		objectList[2]->rotationSpeed.x = 10;
		objectList[3]->rotationSpeed.x = 10;
		break;

	case 't':
		//크레인의맨위팔이 z축에대하여양 / 음방향으로회전한다. 회전각도는90~180도사이로정한다
		objectList[3]->rotationSpeed.z = 10;
		break;

	case 's': //움직임 멈추기
		for (int i = 1; i < 4; ++i) {
			objectList[i]->SetRotationSpeed({ 0,0,0 });
			isRotateX = false;
		}
		break;

	case 'c':// 움직임 초기화
		for (int i = 1; i < 4; ++i) {
			objectList[i]->ResetRotation();
			isRotateX = false;
			objectList[i]->SetRotationSpeed({ 0,0,0 });
			
		}
		
		break;

	case 'q':// 종료
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
	InitDesc desc;
	desc.width = WIDTH;
	desc.height = HEIGHT;


	renderer = new Renderer{ desc };
	renderer->AddShaderWithTwoParam("vertex.glsl", "pixel.glsl", "basic");
	renderer->AddShaderWithTwoParam("lineVertex.glsl", "pixel.glsl", "line");
	renderer->AddShaderWithTwoParam("vertexBasic.glsl", "pixel.glsl", "obj");

	renderer->SetViewMatrix({ 0,1,5 }, { 0,0,0 }, { 0,1,0 });
	renderer->SetProjMatrix(90.f, 0.1f, 100.0f);


	BasicObjectDesc object;
	object.primitiveType = GL_TRIANGLES;

	//바닥 객체 만들기
	Mesh* rectangle = new Mesh();
	rectangle->CreateRectangle();

	MeshObject* plane = new MeshObject();
	plane->Initialize(object, renderer, rectangle, { 0,-0.5,0 }, { 22.5,0,0 }, { 10,7,1 });
	objectList.push_back(plane);


	//크레인 객체 만들기

	meshMap["crane1"] = new Mesh();
	meshMap["crane2"] = new Mesh();
	meshMap["crane3"] = new Mesh();

	meshMap["crane1"]->CreateCube({ 1,0,0 });
	meshMap["crane2"]->CreateCube({ 1,1,0 });
	meshMap["crane3"]->CreateCube({0, 1, 1});

	MeshObject* crane1 = new MeshObject();
	MeshObject* crane2 = new MeshObject();
	MeshObject* crane3 = new MeshObject();

	crane1->Initialize(object, renderer, meshMap["crane1"], {}, {}, { 1,0.5,1 });
	crane2->Initialize(object, renderer, meshMap["crane2"], { 0,0.8,0 }, {}, { 0.5,0.3,1 });
	crane3->Initialize(object, renderer, meshMap["crane3"], { 0,1.6,0 }, {}, { 0.3,0.5,0.5 });
	
	objectList.push_back(crane1);
	objectList.push_back(crane2);
	objectList.push_back(crane3);
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
	convertDeviceXYOpneglXY(x, y, &ox, &oy);
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

	//// Enable depth test
	glEnable(GL_DEPTH_TEST);
	//// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);


	//glEnable(GL_CULL_FACE);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);



	std::chrono::duration<double> diff = chrono::high_resolution_clock::now() - prevTime;
	prevTime = chrono::high_resolution_clock::now();


	renderer->SetCurrentShader("obj");//그리기 전에 어떤 쉐이더로 그릴지 꼭 지정해야뎌!
	for(auto& data:objectList)
	{
		data->Update(diff.count());//월드행렬 계산
		data->Render();//쉐이더한테 값 넘겨주고
	}

	if (objectList[2]->currentAngle.x > 90.f)
	{
		objectList[2]->rotationSpeed.x = -10;
	}
	else if (objectList[2]->currentAngle.x < -90.f)
	{
		objectList[2]->rotationSpeed.x = 10;
	}

	if (objectList[3]->currentAngle.x > 90.f)
	{
		objectList[3]->rotationSpeed.x = -10;
	}
	else if (objectList[3]->currentAngle.x < -90.f)
	{
		objectList[3]->rotationSpeed.x = 10;
	}

	if (objectList[3]->currentAngle.z > 90.f) {
		objectList[3]->rotationSpeed.z = -10;
	}
	else if(objectList[3]->currentAngle.z < -90.f){
		objectList[3]->rotationSpeed.z = 10;
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기 
{
	glViewport(0, 0, w, h);
}


