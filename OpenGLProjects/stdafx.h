#pragma once
#include<vector>
#include<string>
#include <cstdlib>
//#include <stdio.h>
#include <iostream>
#include<chrono>
#include<cstdio>
#include<unordered_map>
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

void convertDeviceXYOpneglXY(int x, int y, float* ox, float* oy);

char* filetobuf(const char *file);

void suthHodgClip(vector<glm::vec3> poly_points, int poly_size,
	vector<glm::vec2>& clipper_points, int clipper_size);


bool CyrusBeck(vector<glm::vec3>& vertices,
	glm::vec2 line[], int n, vector<glm::vec2>& result);




void Print(const glm::vec4& param);
void Print(const glm::vec2& param);