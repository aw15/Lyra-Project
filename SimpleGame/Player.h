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

//Physics//
	virtual void BeginContact(b2Fixture* otherObjectFixture) override final;
	virtual void EndContact(b2Fixture* otherObjectFixture)override final;
	virtual void PreSolve(b2Fixture* otherObjectFixture, const b2Manifold* oldManifold)override final;
	virtual void PostSolve(b2Fixture* otherObjectFixture, const b2ContactImpulse* impulse)override final;
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

