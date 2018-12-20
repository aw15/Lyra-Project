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
#include "MainScene.h"

MainScene *mainScene;





void RenderScene(void)  
{

	static TimePoint prevTime = Time::now();
	static float timeAccumulator = 0;//시간을 누적

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);



	TimePoint currTime = Time::now();
	TimeDuration timediff = currTime - prevTime;
	prevTime = currTime;
	timeAccumulator += timediff.count();
	while (timeAccumulator >= UPDATE_FREQUENCY)
	{
		mainScene->Update(UPDATE_FREQUENCY);
		mainScene->Draw();
		timeAccumulator -= UPDATE_FREQUENCY;
	}
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		x = x - (WIDTH / 2);
		y = (HEIGHT / 2) - y;
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	mainScene->KeyInput(key);


	RenderScene();

}

void KeyUpInput(unsigned char key, int x, int y)
{
	mainScene->KeyUpInput(key);
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{

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
	mainScene = new MainScene();

	//GLUT가 무슨일 있을때 알려주는 함수들
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	
	glutMainLoop();

	delete mainScene;
    return 0;
}

