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
		cameraPosition, // ī�޶�� (4,3,3) �� �ִ�. ���� ��ǥ����
		lookDir, // �׸��� ī�޶� ������ ����
		cameraUp  // �Ӹ��� �����̴� (0,-1,0 ���� �غ���, ������ �����̴�)
	);
}

void Renderer::SetProjMatrix(float fov,float nearZ,float farZ)
{
	projMatrix = glm::perspective(
		glm::radians(fov),  // �������� �þ߰��Դϴ� : "��"�� ũ��. "ī�޶� ����" �� �����غ�����. �̵��� ���� 90�� (����Ʈ�� ���̵�) ���� 30�� (ũ�� Ȯ���� ���) ���̿� �ֽ��ϴ�
		initDesc.width/initDesc.height, // ȭ�� �� �Դϴ�. �̰��� ����� ������ ũ�⿡ �����մϴ�. 4/3 == 800/600 == 1280/960 �ε�, ��� ���� ���� ?
		nearZ,        // Near clipping plane (�ٰŸ� �߶󳻱� ���). �ִ��� ũ�� �ϼ���. �ƴϸ� ��Ȯ�� ������ ���� �� �ֽ��ϴ�.
		farZ       // Far clipping plane (���Ÿ� �߶󳻱� ���). �ִ��� �۰� �ϼ���.
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

	//---���ؽ����̴��о������ϰ��������ϱ� 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexsource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader �����Ͻ���\n" << errorLog << endl;
		return false;
	}

	//---�����׸�Ʈ���̴��о������ϰ��������ϱ�
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentsource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader �����Ͻ���\n" << errorLog << endl;
		return false;
	}
	ShaderProgramID = glCreateProgram(); //---���̴����α׷������
	glAttachShader(ShaderProgramID, vertexShader); // ���̴����α׷������ؽ����̴����̱� 
	glAttachShader(ShaderProgramID, fragmentShader); // ���̴����α׷��������׸�Ʈ���̴����̱�

	glBindAttribLocation(ShaderProgramID, 0, "in_Position");
	glBindAttribLocation(ShaderProgramID, 1, "in_Color");


	glLinkProgram(ShaderProgramID); // ���̴����α׷���ũ�ϱ�
	glDeleteShader(vertexShader); // ���̴����α׷�����ũ�Ͽ����̴���ü��ü�»������� 
	glDeleteShader(fragmentShader);
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // ���̴����߿���Ǿ�����üũ�ϱ� 
	if (!result) {
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		cerr << "ERROR: shader program �������\n" << errorLog << endl;
		return false;
	}
	glUseProgram(ShaderProgramID); //---����������̴����α׷�����ϱ� // �����������α׷�������ְ�, Ư�����α׷�������Ϸ��� // glUseProgram�Լ���ȣ���Ͽ������Ư�����α׷��������Ѵ�. //
}
