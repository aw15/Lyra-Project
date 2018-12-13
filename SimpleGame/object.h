#pragma once
class Object	 //�׸��°� ��Ƴ��
{
private:
	Vector3D position;
	float width = 0.f;
	float height = 0.f;
public:
	Object() = default;
	~Object();
	/////////////////SET/////////////////////////////////////////////
	void SetPosition(Vector3D& position) { this->position = position; }
	////////////////GET////////////////////////////////////////////////
	void GetPosition(Vector3D& position) { position = this->position; }
	///////////////////////////////////////////////////////////////////
	virtual void Move(const Vector3D& dir);
	virtual void Fire();
	///////////////////////////////////////////////////////////////
	virtual void Update(float eTime);
	virtual void Draw(Renderer* renderer);
};

