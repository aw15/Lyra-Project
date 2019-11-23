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

	case 'f': //�����׸����庯��
		if (isPolygonMode == false) {
			glPolygonMode(GL_FRONT, GL_LINE);
			isPolygonMode = true;
		}
		else {
			glPolygonMode(GL_FRONT, GL_FILL);
			isPolygonMode = false;
		}
		break;
		//������� ��� ���	


	case '+'://������¼ӵ� ����.
		speedX = speedX + 0.5;
		speedY = speedY + 0.5;
		break;

	case '-': // �ӵ� ����
		speedX = speedX - 0.5;
		speedY = speedY - 0.5;
		break;

	case 'q': // ����
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
	//�������� �˰��� �׽�Ʈ////////////////////////////////////////////////////////////////////////////
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


	////CyrusBeck �˰���///////////////////////////////////////////////////////////////////////////////////
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
		//��ǥ�躯ȯ

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
int main(int argc, char** argv) // ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(WIDTH, HEIGHT); // �������� ũ�� ����
	window = glutCreateWindow("Example1"); // ������ ����(������ �̸�)

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

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	glDisable(GL_CULL_FACE);

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MousDrag);
	glutSpecialFunc(SpecialInput);
	glutMainLoop(); // �̺�Ʈ ó�� ���� 

	CleanUp();//�޸� ����

	return true;
}


GLvoid drawScene() // �ݹ� �Լ�: ��� 
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �⺻ ���
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

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


	if (shapeSpawnTime > 2.0) { //2�ʸ��� ��ü ����


		auto tempObject = new MeshObject();
		BasicObjectDesc objDesc;
		objDesc.primitiveType = GL_TRIANGLES;
		string meshName;
		if (rand() % 10 > 4)
			meshName = "Triangle";
		else
			meshName = "Rectangle";

		//�����ϰ� ��ü����
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

GLvoid Reshape(int w, int h) // �ݹ� �Լ�: �ٽ� �׸��� 
{
	glViewport(0, 0, w, h);
}


