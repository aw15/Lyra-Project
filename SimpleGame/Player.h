#pragma once
class ObjectState;

class Player:public Object
{
public:
	Player(Renderer* renderer);
	~Player();
	void Draw() override final;
	void Update(float eTime) override final;
	void HandleInput(const char key, KEY_STATUS status) override final;
	//////////////////////INPUT MOVEMENT///////////////////////////////
	void Move(const Vector3D& dir)override final;
	void Idle()override final;
	void AirAttack()override final;
	////////////////////////SET///////////////////////////////////////
	void SetGraphic(const int image);
	virtual void SetState(string name);
	////////////////////////GET///////////////////////////////////////
private:
	int maxAnimationX = 4;
	int maxAnimationY = 1;
	float animationTime = 0;

	unordered_map<string, ObjectState*> states;
	ObjectState* currentState = nullptr;
	InputHandler inputHandler;
	string currentImageName = "";
};

