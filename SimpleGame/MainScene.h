#pragma once

#include "object.h"
class InputHandler;
class MainScene
{
	Renderer *renderer;
	InputHandler* inputHandler;
	Object testObject;
public:
	MainScene();
	~MainScene();
	void Draw();
	void Update(float time);
	void KeyInput(unsigned char key, int x, int y);
};

