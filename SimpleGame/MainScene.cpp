#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene()
{
	renderer = new Renderer(WIDTH,HEIGHT);
	inputHandler = new InputHandler();

}


MainScene::~MainScene()
{
}


void MainScene::Draw()
{
	testObject.Draw(renderer);
}




void MainScene::Update(float time)
{
	

}
	
void MainScene::KeyInput(unsigned char key, int x, int y)
{
	Command* command = inputHandler->handleInput(key);
	if (command)
		command->Execute(&testObject);
}


