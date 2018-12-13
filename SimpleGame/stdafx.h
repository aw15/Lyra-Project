#pragma once


#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <chrono>
#include <vector>
#include<unordered_map>
#include<string>
#include<windows.h>
using namespace std;

#define WIDTH 500
#define HEIGHT 500

#define PLAYER 0
#define PLAYER2 1
#define FRICTION_COEF 5.f //마찰력 크기
#define GRAVITY 9.8f


using Time = std::chrono::high_resolution_clock;
using TimePoint = Time::time_point;
using TimeDuration = std::chrono::duration<float>;//디폴트는 초.

struct Rect
{
	float minx;
	float miny;
	float maxx;
	float maxy;
};

struct Vector3D
{
	float x = 0;
	float y = 0;
	float z = 0;
};

struct Vector2D
{
	float x = 0;
	float y = 0;
};

#include "renderer.h"
#include"object.h"
#include"InputHandler.h"








const float UPDATE_FREQUENCY{ 1.f / 120.f };

float magnitude(float x, float y);


bool isCollide(Rect &standard, Rect &compare);