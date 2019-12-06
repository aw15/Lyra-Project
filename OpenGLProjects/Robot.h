#pragma once
class MeshObject;
class Renderer;

const glm::vec3 moveDirChoice[4] = { {1,0,0},{0,0,1},{-1,0,0},{0,0,-1} };

class Robot : public MeshObject 
{
public:
	Robot();
	~Robot();

	void SetMoveDirAndRotate(const glm::vec3& moveDir);
	void SetMoveDirAndRotate(const int dirIndex);

	//Object의 위치, 회전, 크기 등 상태를 갱신.
	virtual void Update(const float elapsedTime) override;

public:
	glm::vec3 minBoundary = {-INT_MAX,-INT_MAX ,-INT_MAX };
	glm::vec3 maxBoundary = { INT_MAX,INT_MAX ,INT_MAX };

	float speed = 0;
	glm::vec3 moveDir = {0,0,0};
	glm::vec3 lookDir = { 0,0,1 };

	int currentMoveDirIndex = 0;


};

