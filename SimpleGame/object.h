#pragma once
class Object	 //그리는거 모아논거
{
protected:
	Renderer* renderer;

	Vector3D position;
	Color color = {1,1,1,1};
	Vector3D dir;
	Vector3D velocity = {10,10};
	float width = 0.f;
	float height = 0.f;

public:
	Object(Renderer* renderer);
	virtual ~Object();
	/////////////////SET/////////////////////////////////////////////
	void SetPosition(Vector3D& position) { this->position = position; }
	virtual void SetState(string name) = 0;
	virtual void SetGraphic(const int image) =0;
	////////////////GET////////////////////////////////////////////////
	void GetPosition(Vector3D& position) { position = this->position; }
	////////////////////////INPUT MOVEMENT/////////////////////////////
	virtual void Move(const Vector3D& dir);
	virtual void Idle();
	virtual void Fire();
	virtual void AirAttack();
	///////////////////////////////////////////////////////////////
	virtual void Update(float eTime) = 0;
	virtual void Draw() = 0;
	virtual void HandleInput(const char key, KEY_STATUS status) = 0;
};

