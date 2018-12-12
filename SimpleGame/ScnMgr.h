#pragma once

#include "object.h"

class ScnMgr
{
	Renderer *m_render;

	
public:
	ScnMgr();
	~ScnMgr();

	void Draw();
	void Update(float time);
	void KeyInput(unsigned char key, int x, int y);
	void KeyUpInput(unsigned char key, int x, int y);
	void SpecialKeyInput(unsigned char key, int x, int y);
};

