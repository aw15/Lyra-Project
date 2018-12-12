#pragma once


#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <vector>
#include<windows.h>

#include "targetver.h"
#include "renderer.h"
#include"object.h"

using namespace std;



#define PLAYER 0
#define PLAYER2 1
#define FRICTION_COEF 5.f //마찰력 크기
#define GRAVITY 9.8f
#define KEY_FORCE 1000.0f
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80


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
	float x=0;
	float y=0;
	float z = 0;
};

struct Vector2D
{
	float x = 0;
	float y = 0;
};

const float UPDATE_FREQUENCY{ 1.f / 120.f };

float magnitude(float x, float y);


bool isCollide(Rect &standard, Rect &compare);