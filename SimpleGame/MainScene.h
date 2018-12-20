#pragma once

#include "object.h"
class InputHandler;
class MainScene
{
	Renderer *renderer;
	InputHandler* inputHandler;
	Object *testObject;
public:
	MainScene();
	~MainScene();
	void MakeTexture();
	void Draw();
	void Update(float time);
	void KeyInput(unsigned char key);
	void KeyUpInput(unsigned char key);
};

