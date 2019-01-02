#pragma once
class ObjectState;

class Player:public Object
{
public:
	Player(Renderer* renderer);
	~Player();
	virtual void InitPhysics() override final;
	/////////////////////////////////////////////////////////////////
	void Draw() override final;
	void Update() override final;
	void HandleInput(const char key, KeyStatus status) override final;
	//////////////////////INPUT MOVEMENT///////////////////////////////
	void Move(const Vector3D& dir)override final;
	void Idle()override final;
	void AirAttack()override final;
	////////////////////////SET///////////////////////////////////////
	void SetGraphic(const unsigned int image);
	////////////////////////GET///////////////////////////////////////
private:
	int maxAnimationX;
	int maxAnimationY;
	float animationTime;

	InputHandler inputHandler;
	string currentImageName;

	PlayerState playerState;
	////PHYSICS//////////////////////////
	PhysicsComponent* physics;
	//b2PolygonShape dynamicBox;
	//b2Body* body;
	//b2Fixture* fixture;
	
};

