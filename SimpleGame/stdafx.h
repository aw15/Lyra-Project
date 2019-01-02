#pragma once


#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <chrono>
#include <vector>
#include<unordered_map>
#include<string>
#include<windows.h>
#include<memory.h>
#include"Box2D/Box2D.h"
using namespace std;

#define WIDTH 500
#define HEIGHT 500
/////////////////////PHYSICS//////////////////////////////////////
#define PLAYER_GROUP -1
#define ENEMY_GROUP -2
#define GRAVITY -9.8f
const float PPM_RATIO  = 100.f;
const float UPDATE_FREQUENCY{ 1.f / 60.f };
//PLAYER_IMAGE
#define IDLE_IMAGE 0b0000'0001u
#define RUN_IMAGE 0b0000'0010u
#define AIR_ATTACK_IMAGE 0b000'0100u

#define TOPIXEL(x) (round(x*PPM_RATIO))
#define TOMETER(x) (x/PPM_RATIO)
#define TurnOn(a,b) a |= b
#define TurnOff(a,b) a &=~b

//PLAYER_STATE
enum class PlayerState
{
	IDLE,
	RUN,
	AIRATTACK
};


enum class AIState
{
	IDLE,
	MOVE_RIGHT,
	MOVE_LEFT
};

//INPUT
enum KeyStatus
{
	PRESS,
	RELEASE
};

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

struct Color
{
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 0;
};



struct Vector3D
{
	float x = 0;
	float y = 0;
	float z = 0;

	void Set(const float x, const float y, const float z) { this->x = x; this->y = y; this->z = z; }
	Vector3D Get() const { return Vector3D{ x,y,z }; }
	void ToPixel(Vector3D& vec) { vec.x = round(x * PPM_RATIO); vec.y = round(y * PPM_RATIO); vec.z = round(z * PPM_RATIO);}
	void ToPixel() { x = round(x * PPM_RATIO); y = round(y * PPM_RATIO); z = round(z * PPM_RATIO); }

	void ToMeter(Vector3D& vec) { vec.x = x / PPM_RATIO; vec.y = y / PPM_RATIO; vec.z = z / PPM_RATIO; }
	void ToMeter() { x = x / PPM_RATIO; y = y / PPM_RATIO; z = z / PPM_RATIO; }

	void operator=(const b2Vec2& param) { x = param.x; y = param.y; }

	void Print() { printf("position : %f %f %f\n", x, y, z); }
};

struct Vector2D
{
	float x = 0;
	float y = 0;
};


#include "renderer.h"
#include"PhysicsEngine.h"
#include"PhysicsComponent.h"
#include"InputHandler.h"
#include"object.h"





float magnitude(float x, float y);

bool isCollide(Rect &standard, Rect &compare);