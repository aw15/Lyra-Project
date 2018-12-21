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
using namespace std;

#define WIDTH 500
#define HEIGHT 500

#define PLAYER 0
#define PLAYER2 1
#define FRICTION_COEF 5.f //마찰력 크기
#define GRAVITY 9.8f

//PLAYER_IMAGE
#define IDLE_IMAGE 0b0000'0001u
#define RUN_IMAGE 0x0000'0010u
#define AIR_ATTACK_IMAGE 0b000'0100u


#define TurnOn(a,b) a |= b
#define TurnOff(a,b) a &=~b

//PLAYER_STATE
enum class State
{
	IDLE,
	RUN,
	AIRATTACK
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
};

struct Vector2D
{
	float x = 0;
	float y = 0;
};


#include "renderer.h"
#include"InputHandler.h"
#include "PlayerState.h"
#include"object.h"
#include"Player.h"

const float UPDATE_FREQUENCY{ 1.f / 120.f };

float magnitude(float x, float y);

bool isCollide(Rect &standard, Rect &compare);