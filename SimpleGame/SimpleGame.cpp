/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "ScnMgr.h"

ScnMgr *m_ScnMgr;

TimePoint g_PrevTime = Time::now();
float g_timeAccumulator = 0;//�ð��� ����


void RenderScene(void)  
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	TimePoint currTime = Time::now();
	float elapsedTime = TimeDuration(currTime - g_PrevTime).count();
	g_PrevTime = currTime;
	
	g_timeAccumulator += elapsedTime;

	while (g_timeAccumulator >= UPDATE_FREQUENCY)//float�� ����Ҽ��� ������ ���ϱ� ���� �ð��� ������Ʈ���� �ٷ���
	{
		m_ScnMgr->Update(UPDATE_FREQUENCY);
		g_timeAccumulator -= UPDATE_FREQUENCY;
	}

	m_ScnMgr->Draw();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		x = x - (500 / 2);
		y = (500 / 2) - y;
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	m_ScnMgr->KeyInput(key, x, y);


	RenderScene();

}

void KeyUpInput(unsigned char key, int x, int y)
{
	m_ScnMgr->KeyUpInput(key, x, y);

	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	m_ScnMgr->SpecialKeyInput(key, x, y);

	RenderScene();
}

int main(int argc, char **argv)
{

	
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	m_ScnMgr = new ScnMgr();

	//GLUT�� ������ ������ �˷��ִ� �Լ���
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF); //Ű���� �Է� �Լ� �ѹ��� �θ��� ���ִ°�
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	
	glutMainLoop();

	delete m_ScnMgr;
    return 0;
}

