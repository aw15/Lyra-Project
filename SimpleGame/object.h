#pragma once
class Object	 //그리는거 모아논거
{
protected:
	Renderer* renderer;

	Vector3D position;
	Color color = {1,1,1,1};
	Vector3D dir;
	Vector3D speed = {0,0};

	float width = 1.f;
	float height = 1.f;
	
	float hp =0;
public:
	Object(Renderer* renderer);
	virtual ~Object();
	virtual void InitPhysics() {};
	/////////////////SET/////////////////////////////////////////////
	void SetPosition(const Vector3D& position) { this->position = position; }
	void SetPosition(const float x, const float y, const float z) { position.x = x; position.y = y; position.z = z; }
	virtual void SetGraphic(const unsigned int image) =0;
	void SetSize(const float w, const float h) { width = w; height = h; }
	void Sethp(const float hp) { this->hp = hp; }
	////////////////GET////////////////////////////////////////////////
	void GetPosition(Vector3D& position) const { position = this->position; }
	float GetHp() const { return hp; };
	float GetHp(float& hp) const { hp = this->hp; };
	////////////////////////INPUT MOVEMENT/////////////////////////////
	virtual void Move(const Vector3D& dir);
	virtual void Idle();
	virtual void Fire();
	virtual void AirAttack();
	///////////////////////////////////////////////////////////////
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void HandleInput(const char key, KeyStatus status) {};
	//Physics//
	virtual void BeginContact(b2Fixture* otherObjectFixture) {};
	virtual void EndContact(b2Fixture* otherObjectFixture) {};
	virtual void PreSolve(b2Fixture* otherObjectFixture, const b2Manifold* oldManifold) {};
	virtual void PostSolve(b2Fixture* otherObjectFixture, const b2ContactImpulse* impulse) {};

};

