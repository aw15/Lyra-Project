#pragma once
class Slime:public Object
{
private:
	const string texture = "slime";
public:
	Slime(Renderer* renderer);
	~Slime();

	virtual void InitPhysics() override final;
	/////////////////////////////////////////////////////////////////
	void Draw() override final;
	void Update() override final;
	void HandleAI(const AIState state);
	//////////////////////INPUT MOVEMENT///////////////////////////////
	void Move(const Vector3D& dir)override final;
	void Idle()override final;
	////////////////////////SET///////////////////////////////////////
	void SetGraphic(const unsigned int image);
	////////////////////////GET///////////////////////////////////////

//PHYSICS//
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

	AIState slimeState;
	////PHYSICS//////////////////////////
	PhysicsComponent* physics;
};
