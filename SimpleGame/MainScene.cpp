#include "stdafx.h"
#include "MainScene.h"
#include"Slime.h"
#include"Player.h"

MainScene::MainScene()
{
	renderer = new Renderer(WIDTH,HEIGHT);
	inputHandler = new InputHandler();
	PhysicsEngine::Initialize();
	PhysicsEngine::world.SetContactListener(this);
	MakeTexture();

	player = new Player(renderer);
	player->InitPhysics();

	slime = new Slime(renderer);
	//위치 설정 후에 물리효과를 실행할것.
	slime->SetPosition(2, 0, 0);
	slime->InitPhysics();
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
	//SLIME//
	renderer->CreatePngTexture("../SimpleGame/Resource/monster/blob idle.png", "slime_idle");
	renderer->CreatePngTexture("../SimpleGame/Resource/monster/blob attack.png", "slime_attack");

}

void MainScene::Draw()
{
	player->Draw();
	slime->Draw();
}

void MainScene::Update(float time)
{
	PhysicsEngine::Update();
	player->Update();
	//slime->Update();
}

void MainScene::KeyUpInput(unsigned char key)
{
	player->HandleInput(key, KeyStatus::RELEASE);
}

void MainScene::BeginContact(b2Contact * contact)
{

	short contactObjectA = contact->GetFixtureA()->GetFilterData().groupIndex;
	short contactObjectB = contact->GetFixtureB()->GetFilterData().groupIndex;


	switch (contactObjectA)//상대편 충돌체를 넘겨줌.
	{
	case ENEMY_GROUP:
		slime->BeginContact(contact->GetFixtureB());
		break;
	case PLAYER_GROUP:
		player->BeginContact(contact->GetFixtureB());
		break;
	}

	//switch (contactObjectB)
	//{
	//case ENEMY_GROUP:
	//	slime->BeginContact(contact->GetFixtureA());
	//	break;
	//case PLAYER_GROUP:
	//	player->BeginContact(contact->GetFixtureA());
	//	break;
	//}
}

void MainScene::EndContact(b2Contact * contact)
{
}

void MainScene::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
}

void MainScene::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
}
	
void MainScene::KeyInput(unsigned char key)
{
	player->HandleInput(key, KeyStatus::PRESS);
}


