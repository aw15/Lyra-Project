#pragma once

#include "object.h"
class InputHandler;
class Slime;
class Player;

class MainScene: public b2ContactListener
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
	//Physics
	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

};

