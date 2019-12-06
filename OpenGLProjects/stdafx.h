#pragma once
#include<vector>
#include<string>
#include <cstdlib>
#include<climits>
//#include <stdio.h>
#include <iostream>
#include<chrono>
#include<cstdio>
#include<unordered_map>
#include<fstream>
#include <sstream>
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
#define PI 3.141592f

struct BasicObjectDesc
{
	GLuint primitiveType = GL_TRIANGLES;
};



struct VertexData
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
};


const glm::vec4 BASIC_COLOR[5] = { {1,0,0, 1},{0,1,0, 1},{0,0,1, 1},{1,1,0, 1},{0,1,1,1} };

enum COLOR
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	CYAN
};

void convertDeviceXYOpneglXY(int x, int y, float* ox, float* oy);

char* filetobuf(const char *file);




void Print(const glm::vec4& param, string tag = "temp : ");
void Print(const glm::vec3& param, string tag = "temp : ");
void Print(const glm::vec2& param, string tag = "temp : ");



void stringTokenize(vector<string>& result, string& s, char delim);


float GetAngle(const glm::vec3& a, const glm::vec3& b);
