#pragma once
class Object	 //그리는거 모아논거
{
protected:
	Renderer* renderer;

	Vector3D position;
	Color color = {1,1,1,1};
	Vector3D dir;
	Vector3D velocity = {0.02,0.02};

	float width = 0.f;
	float height = 0.f;

public:
	Object(Renderer* renderer);
	virtual ~Object();
	virtual void InitPhysics() {};
	/////////////////SET/////////////////////////////////////////////
	void SetPosition(Vector3D& position) { this->position = position; }
	virtual void SetGraphic(const unsigned int image) =0;
	void SetSize(const float w, const float h) { width = w; height = h; }
	////////////////GET////////////////////////////////////////////////
	void GetPosition(Vector3D& position) { position = this->position; }
	////////////////////////INPUT MOVEMENT/////////////////////////////
	virtual void Move(const Vector3D& dir);
	virtual void Idle();
	virtual void Fire();
	virtual void AirAttack();
	///////////////////////////////////////////////////////////////
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void HandleInput(const char key, KeyStatus status) = 0;
};

