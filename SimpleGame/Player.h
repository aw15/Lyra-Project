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
	int maxAnimationX = 4;
	int maxAnimationY = 1;
	float animationTime = 0;

	InputHandler inputHandler;
	string currentImageName = "";

	State playerState = State::IDLE;
	////PHYSICS//////////////////////////
	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2BodyDef bodyDef;
	b2Body* body;
};
