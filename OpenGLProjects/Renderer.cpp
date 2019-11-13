#include"stdafx.h"
#include "Renderer.h"




Renderer::Renderer(InitDesc initDesc)
{
	this->initDesc = initDesc;
}

bool Renderer::Initialize()
{
	CompileShader();

	return true;
}

void Renderer::SetViewMatrix(const glm::vec3& cameraPosition,const glm::vec3& lookDir,const glm::vec3& cameraUp)
{
	viewMatrix = glm::lookAt(
		cameraPosition, // 카메라는 (4,3,3) 에 있다. 월드 좌표에서
		lookDir, // 그리고 카메라가 원점을 본다
		cameraUp  // 머리가 위쪽이다 (0,-1,0 으로 해보면, 뒤집어 볼것이다)
	);
}

void Renderer::SetProjMatrix(float fov,float nearZ,float farZ)
{
	projMatrix = glm::perspective(
		glm::radians(fov),  // 수직방향 시야각입니다 : "줌"의 크기. "카메라 렌즈" 를 생각해보세요. 이들은 보통 90도 (엑스트라 와이드) 에서 30도 (크게 확대한 경우) 사이에 있습니다
		initDesc.width/initDesc.height, // 화면 비 입니다. 이것은 당신의 윈도우 크기에 의존합니다. 4/3 == 800/600 == 1280/960 인데, 어디서 본것 같죠 ?
		nearZ,        // Near clipping plane (근거리 잘라내기 평면). 최대한 크게 하세요. 아니면 정확도 문제가 생길 수 있습니다.
		farZ       // Far clipping plane (원거리 잘라내기 평면). 최대한 작게 하세요.
	);
}

Renderer::~Renderer()
{
}

void Renderer::DrawPrimitiveObject(const int primitiveType, GLuint vao, const int count)
{
	glBindVertexArray(vao);
	glDrawArrays(primitiveType, 0, count);
	
}

bool Renderer::CompileShader()
{
	auto vertexsource = filetobuf(initDesc.vertexShaderPath.c_str());
	auto fragmentsource = filetobuf(initDesc.pixelShaderPath.c_str());

	//---버텍스세이더읽어저장하고컴파일하기 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexsource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader 컴파일실패\n" << errorLog << endl;
		return false;
	}

	//---프래그먼트세이더읽어저장하고컴파일하기
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentsource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader 컴파일실패\n" << errorLog << endl;
		return false;
	}
	ShaderProgramID = glCreateProgram(); //---세이더프로그램만들기
	glAttachShader(ShaderProgramID, vertexShader); // 세이더프로그램에버텍스세이더붙이기 
	glAttachShader(ShaderProgramID, fragmentShader); // 세이더프로그램에프래그먼트세이더붙이기

	glBindAttribLocation(ShaderProgramID, 0, "in_Position");
	glBindAttribLocation(ShaderProgramID, 1, "in_Color");


	glLinkProgram(ShaderProgramID); // 세이더프로그램링크하기
	glDeleteShader(vertexShader); // 세이더프로그램에링크하여세이더객체자체는삭제가능 
	glDeleteShader(fragmentShader);
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // 세이더가잘연결되었는지체크하기 
	if (!result) {
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		cerr << "ERROR: shader program 연결실패\n" << errorLog << endl;
		return false;
	}
	glUseProgram(ShaderProgramID); //---만들어진세이더프로그램사용하기 // 여러개의프로그램만들수있고, 특정프로그램을사용하려면 // glUseProgram함수를호출하여사용할특정프로그램을지정한다. //
}
