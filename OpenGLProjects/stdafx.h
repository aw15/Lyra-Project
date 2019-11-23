#pragma once
#include<vector>
#include<string>
#include <cstdlib>
//#include <stdio.h>
#include <iostream>
#include<chrono>
#include<cstdio>
#include<unordered_map>
#include<set>
#include<thread>
#include<mutex>
#include<future>
#include<fstream>
#include<sstream>

//OpenGL
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"



using namespace std;

#define WIDTH 700
#define HEIGHT 700
#define UPDATE_RATIO 16

enum class BasicShapeType
{
	SPHERE,
	CONE,
	CYLINDER,
	DISK,
	CUBE,
	PYRAMID
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


void Print(glm::vec3 param, const char* name = "point = ");

vector<string> stringTokenize(const string& data, const char delimiter = ' ');