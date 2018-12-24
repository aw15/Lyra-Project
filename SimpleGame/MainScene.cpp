#include "stdafx.h"
#include "MainScene.h"


MainScene::MainScene()
{
	renderer = new Renderer(WIDTH,HEIGHT);
	inputHandler = new InputHandler();
	PhysicsComponent::Initialize();


	testObject = new Player(renderer);
	testObject->InitPhysics();

	MakeTexture();

}


MainScene::~MainScene()
{
}

void MainScene::MakeTexture()
{
	renderer->CreatePngTexture("../SimpleGame/Resource/player/airattack1.png", "player_airAttack1");
	renderer->CreatePngTexture("../SimpleGame/Resource/player/idle1.png", "player_idle1");
	renderer->CreatePngTexture("../SimpleGame/Resource/player/jump.png", "player_jump");
	renderer->CreatePngTexture("../SimpleGame/Resource/player/run.png", "player_run");
}


void MainScene::Draw()
{
	testObject->Draw();
}




void MainScene::Update(float time)
{
	PhysicsComponent::Update();
	testObject->Update();
}

void MainScene::KeyUpInput(unsigned char key)
{
	testObject->HandleInput(key, KeyStatus::RELEASE);
}




	
void MainScene::KeyInput(unsigned char key)
{
	testObject->HandleInput(key, KeyStatus::PRESS);
}


