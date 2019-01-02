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
