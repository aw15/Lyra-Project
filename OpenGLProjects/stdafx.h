#pragma once
#include<vector>
#include<string>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include<chrono>

//OpenGL
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"



using namespace std;

#define WIDTH 800
#define HEIGHT 600



enum class BasicShapeType
{
	SPHERE,
	CONE,
	CYLINDER
};


enum class ObjectType
{
	BasicType,
	MeshType
};


struct BasicObjectDesc
{
	GLuint primitiveType = GL_TRIANGLES;
	BasicShapeType basicType = BasicShapeType::SPHERE;
};

void convertDeviceXYOpneglXY(int x, int y, float* ox, float* oy) { // 윈도우좌표를 OpenGL좌표로 변환
	int w = WIDTH;
	int h = HEIGHT;
	*ox = (float)((x - (float)w / 2.0)*(float)(1.0 / (float)(w / 2.0)));
	*oy = -(float)((y - (float)h / 2.0)*(float)(1.0 / (float)(h / 2.0)));
}

char* filetobuf(const char *file);


