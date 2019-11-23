#include"stdafx.h"
#include"Renderer.h"
#include "BasicObject.h"
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
	//float poly_size = 3;
	//vector<glm::vec3> poly_points = { {0,50,0}, {-50,0,0},
	//						  {50,0,0} };

	//// Defining clipper polygon vertices in clockwise order 
	//// 1st Example with square clipper 
	//float clipper_size = 4;
	//vector<glm::vec2> clipper_points= { {0,100}, {0,-100},
	//						  {1200,-100}, {1200,100} };

	//suthHodgClip(poly_points, poly_size, clipper_points,
	//	clipper_size);

	//physics.SetCohenSutherlandTarget({ -0.5,-0.5,0 }, { 0.5,0.5,0 });
	//physics.CohenSutherlandClip(0, 100, 0, -100);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////


	////CyrusBeck 알고리즘///////////////////////////////////////////////////////////////////////////////////
	//vector<glm::vec3> vertices
	//	= { {200, 50, 0},
	//		{250, 100, 0},
	//		{200, 150, 0},{100,150,0},{50,100,0},{100,50,0} };

	//// Make sure that the vertices 
	//// are put in a clockwise order 
	//glm::vec2 line[] = { {150, 0} , {150,500} };

	//vector<glm::vec2> result;
	//auto r = CyrusBeck(vertices, line, vertices.size(), result);
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


	auto tempObject = new MeshObject();
	BasicObjectDesc objDesc;
	objDesc.primitiveType = GL_TRIANGLES;
	string meshName;
	meshName = "Rectangle";

	tempObject->Initialize(objDesc, renderer, meshMap[meshName], { 0,0,0 }, { 0,0,0 }, { 0.5,0.5,0});
	
	objectList.push_back(tempObject);

	tempObject = new MeshObject();
	objDesc.primitiveType = GL_TRIANGLES;
	meshName = "Rectangle";

	tempObject->Initialize(objDesc, renderer, meshMap[meshName], { -100,0,0 }, { 0,0,0 }, { 0.5,0.5,0 });

	objectList.push_back(tempObject);
	

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

		//cout << ox << " " << oy << endl;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		isLineComplete = false;



		for (auto iter = objectList.begin() ; iter != objectList.end();iter++)
		{
			vector<glm::vec3> result;
			int clipDir = 0;

			glm::vec4 min = objectList[0]->GetFinalMatrix() * glm::vec4{ objectList[0]->mesh->vertices[1],0 };
			glm::vec4 max = objectList[0]->GetFinalMatrix() *glm::vec4{ objectList[0]->mesh->vertices[2],0 };
			physics.SetCohenSutherlandTarget(min, max);
			physics.CohenSutherlandClip(mouseStartX, mouseStartY, mouseEndX, mouseEndY, result, clipDir);

			if (result.size() == 2)
			{
				auto mesh1 = new Mesh;
				auto mesh2 = new Mesh;

				auto object1 = new MeshObject();
				auto object2 = new MeshObject();
				BasicObjectDesc objDesc;
				glm::vec3 color1{ 1,0,0 };
				glm::vec3 color2{ 0,1,0 };

				if (clipDir == TOP_DOWN)
				{

					
					mesh1->CreateMeshByVertices(
						{ glm::vec3{min.x,min.y,0}, glm::vec3{min.x,max.y,0}, result[0],result[0], result[1], min },
						{ color1,color1,color1, color1, color1, color1 }
					);

					mesh2->CreateMeshByVertices(
						{ result[0], max, result[1], result[1], {max.x,min.y,0}, max },
						{color2,color2,color2,color2,color2, color2}

					);



					objDesc.primitiveType = GL_TRIANGLES;
					object1->Initialize(objDesc, renderer, mesh1, { 0,0,0 }, { 0,0,0 }, { 1,1,0 }, {0,-0.1,0});

					(*iter)->isActive = false;
					meshes.push_back(mesh1);
					meshes.push_back(mesh2);
					objectList.push_back(object1);

					object2->Initialize(objDesc, renderer, mesh2, { 0,0,0 }, { 0,0,0 }, { 1,1,0 }, { 0,-0.05,0 });
					objectList.push_back(object2);
	
				}
				if (clipDir == LEFT_RIGHT)
				{
					mesh1->CreateMeshByVertices(
						{ glm::vec3{min.x,min.y,0}, result[0],result[1], result[1],{max.x,min.y,0}, min },
						{ color1,color1,color1, color1, color1, color1 }
					);

					mesh2->CreateMeshByVertices(
						{ result[0], result[1], max , max, {min.x,max.y,0}, result[0] },
						{ color2,color2,color2,color2,color2, color2 }

					);



					objDesc.primitiveType = GL_TRIANGLES;
					object1->Initialize(objDesc, renderer, mesh1, { 0,0,0 }, { 0,0,0 }, { 1,1,0 }, { 0,-0.1,0 });

					(*iter)->isActive = false;
					meshes.push_back(mesh1);
					meshes.push_back(mesh2);
					objectList.push_back(object1);

					object2->Initialize(objDesc, renderer, mesh2, { 0,0,0 }, { 0,0,0 }, { 1,1,0 }, { 0,-0.05,0 });
					objectList.push_back(object2);
				}


				break;
			}
		}


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
		if (data->isActive)
		{
			data->Update(diff.count());
			data->Render(renderer->shaderProgramMap["basic"]);
		}
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
		auto tempObject2 = new MeshObject();
		BasicObjectDesc objDesc;
		objDesc.primitiveType = GL_TRIANGLES;
		string meshName = "Rectangle";


		//랜덤하게 객체생성
		if (rand()%10 > 4) {
			tempObject->Initialize(objDesc, renderer, meshMap[meshName], { -1,0,0 }, { 0,0,0 }, { 0.3, 0.3 , 1 }, { speedX,speedY,0 });
		}
		else {
			tempObject->Initialize(objDesc, renderer, meshMap[meshName], { 1,0,0 }, { 0,0,0 }, { 0.3 ,0.3 , 1}, { -speedX,speedY,0 });
		}


		tempObject2->Initialize(objDesc, renderer, meshMap[meshName], { 0,0,0 }, { 0,0,0 }, { 0.5 ,0.5 , 1 });
		objectList.push_back(tempObject);
		objectList.push_back(tempObject2);
		shapeSpawnTime = 0.0f;
	}


	
	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기 
{
	glViewport(0, 0, w, h);
}


