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


#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

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

void suthHodgClip(vector<glm::vec2> poly_points, int poly_size,
	vector<glm::vec2>& clipper_points, int clipper_size);


bool CyrusBeck(glm::vec2 vertices[],
	glm::vec2 line[], int n, vector<glm::vec2>& result);