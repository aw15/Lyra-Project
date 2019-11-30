#pragma once
#include<vector>
#include<string>
#include <cstdlib>
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


void convertDeviceXYOpneglXY(int x, int y, float* ox, float* oy);

char* filetobuf(const char *file);




void Print(const glm::vec4& param, string tag = "temp : ");
void Print(const glm::vec3& param, string tag = "temp : ");
void Print(const glm::vec2& param, string tag = "temp : ");



void stringTokenize(vector<string>& result, string& s, char delim);