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
	glutMainLoop(); // �̺�Ʈ ó�� ���� 

	return true;
}

GLUquadricObj* qobj = gluNewQuadric();

GLvoid drawScene() // �ݹ� �Լ�: ��� 
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �⺻ ���
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

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

GLvoid Reshape(int w, int h) // �ݹ� �Լ�: �ٽ� �׸��� 
{
	glViewport(0, 0, w, h);
}

