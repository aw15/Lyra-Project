#pragma once

#include "object.h"
class InputHandler;
class Slime;
class Player;

class MainScene
{
	Renderer *renderer;
	InputHandler* inputHandler;
	Player *player;
	Slime *slime;


	PhysicsEngine physics;
public:
	MainScene();
	~MainScene();
	void MakeTexture();
	void Draw();
	void Update(float time);
	void KeyInput(unsigned char key);
	void KeyUpInput(unsigned char key);
};

