#include"stdafx.h"
#include"Renderer.h"
#include "Object.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);


static const float cube_vertices[] = {
	/* front surface is blue */
	-0.5,  0.5, 0.5,
	-0.5, -0.5, 0.5,
	 0.5, -0.5, 0.5,
	 0.5,  0.5, 0.5,
	 /* left surface is green */
	 -0.5,  0.5,  0.5,
	 -0.5,  0.5, -0.5,
	 -0.5, -0.5, -0.5,
	 -0.5, -0.5,  0.5,
	 /* top surface is red */
	 -0.5, 0.5, 0.5,
	  0.5, 0.5, 0.5,
	  0.5, 0.5, -0.5,
	 -0.5, 0.5, -0.5,
	 /* right surface is yellow */
	  0.5,  0.5, -0.5,
	  0.5,  0.5,  0.5,
	  0.5, -0.5,  0.5,
	  0.5, -0.5, -0.5,
	  /* back surface is cyan */
	  -0.5,  0.5, -0.5,
	   0.5,  0.5, -0.5,
	   0.5, -0.5, -0.5,
	  -0.5, -0.5, -0.5,
	  /* bottom surface is magenta */
	  -0.5, -0.5, -0.5,
	  -0.5, -0.5,  0.5,
	   0.5, -0.5,  0.5,
	   0.5, -0.5, -0.5,
};


void Keyboard(unsigned char key, int x, int y)
{
	//switch (key) {

	//case 'f': //도형그리기모드변경
	//	if (polygonMode == false) {
	//		glPolygonMode(GL_FRONT, GL_LINE);
	//		polygonMode = true;
	//	}
	//	else {
	//		glPolygonMode(GL_FRONT, GL_FILL);
	//		polygonMode = false;
	//	}
	//	break;

	//case 'm': //4개의 사각형이 시계반대방향으로 이동 (밖으로 나가지않는다.)
	//	if (isMove != true) {

	//		isMove = true;
	//	}
	//	break;

	//case 's': // 멈추기
	//	isMove = false;
	//	break;

	//case 'c'://사각형의 색상바꾸기
	//	srand(time(NULL));
	//	colors[triangleIndex * 3] = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX, rand() / (float)RAND_MAX };
	//	colors[triangleIndex * 3 + 1] = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX, rand() / (float)RAND_MAX };
	//	colors[triangleIndex * 3 + 2] = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX, rand() / (float)RAND_MAX };

	//	triangleIndex += 1;
	//	triangleIndex %= 4;
	//	break;

	//case 'q':
	//	glutDestroyWindow(WIN);
	//	break;
	//}
}



Renderer* renderer;

vector<Object*> objectList;
ObjectDesc objDesc;

void Initialize()
{
	InitDesc desc;
	desc.height = WIDTH;
	desc.height = HEIGHT;
	desc.vertexShaderPath = "vertex.glsl";
	desc.pixelShaderPath = "pixel.glsl";
	renderer = new Renderer{ desc };
	renderer->Initialize();
	renderer->SetViewMatrix({ 0,0,-10 }, { 0,0,0 }, { 0,1,0 });
	renderer->SetProjMatrix(90.f, 0.0f, 1.0f);

	auto tempObject = new Object();

	objDesc.mesh.vertex.push_back({ 0, 0.5, 0 });
	objDesc.mesh.vertex.push_back({ -1, 0, 0 });
	objDesc.mesh.vertex.push_back({1, 0, 0});

	objDesc.mesh.color.push_back({ 1, 1, 0 });
	objDesc.mesh.color.push_back({ 1, 0, 0 });
	objDesc.mesh.color.push_back({ 1, 0, 0 });

	tempObject->Initialize(objDesc);

	objectList.push_back(tempObject);
}

void main(int argc, char** argv) // 윈도우 출력하고 콜백함수 설정 
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
}

GLvoid drawScene() // 콜백 함수: 출력 
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 기본 흰색
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glUseProgram(renderer->ShaderProgramID);

	//GLuint vao;
	//GLuint vbo[2];
	//// VAO 를지정하고할당하기 
	//glGenVertexArrays(1, &vao);
	//// VAO를바인드하기 
	//glBindVertexArray(vao);


	//// 2개의 VBO를지정하고할당하기 
	//glGenBuffers(2, vbo);
	////--- 1번째 VBO를활성화하여바인드하고, 버텍스속성 (좌표값)을저장 
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//for (auto data : objDesc.mesh.vertex)
	//{
	//	cout << data.x << endl;
	//}

	//// 변수 diamond 에서버텍스데이터값을버퍼에복사한다.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* objDesc.mesh.vertex.size(), &objDesc.mesh.vertex[0], GL_STATIC_DRAW);
	//// 좌표값을 attribute 인덱스 0번에명시한다: 버텍스당 3* float 
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//// attribute 인덱스 0번을사용가능하게함 
	//glEnableVertexAttribArray(0);

	////---2번째 VBO를활성화하여바인드하고, 버텍스속성 (색상)을저장 
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//// 변수 colors에서버텍스색상을복사한다. 
	//// colors 배열의사이즈: 9 *float 
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * objDesc.mesh.color.size() , &objDesc.mesh.color[0], GL_STATIC_DRAW);
	//// 색상값을 attribute 인덱스 1번에명시한다: 버텍스당3*float 
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//// attribute 인덱스 1번을사용가능하게함. 
	//glEnableVertexAttribArray(1);
	//glm::mat4 finalMatrix{};
	//glUniformMatrix4fv(glGetUniformLocation(renderer->ShaderProgramID, "transform"), 1, GL_FALSE, glm::value_ptr(finalMatrix));

	//glBindVertexArray(vao);
	//glPointSize(10.0f);
	//glDrawArrays(GL_POINTS, 0, 3);


	for (auto& const data : objectList)
	{
		data->Render(renderer);
	}

	
	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기 
{
	glViewport(0, 0, w, h);
}

