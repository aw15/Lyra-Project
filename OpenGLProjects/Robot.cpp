#include "stdafx.h"

#include"MeshObject.h"
#include "Renderer.h"

#include "Robot.h"

Robot::Robot()
{
}


Robot::~Robot()
{
}

void Robot::SetMoveDirAndRotate(const glm::vec3& moveDir)
{
	auto normalizeDir = glm::normalize(moveDir);

	//cout << acos(glm::dot(glm::vec2{ lookDir.x,lookDir.z }, glm::vec2{ moveDir.x,moveDir.z }))  * (180/PI)<< endl;


//	cout << GetAngle(lookDir,moveDir) * (180/PI) <<endl;


	SetRotationRadian({ 0,GetAngle(lookDir, normalizeDir),0 });

	this->moveDir = normalizeDir;
}

void Robot::SetMoveDirAndRotate(const int dirIndex)
{
	currentMoveDirIndex = dirIndex;
	SetMoveDirAndRotate(moveDirChoice[dirIndex]);
}


void Robot::Update(const float elapsedTime)
{
	Translate(speed * moveDir * (float)elapsedTime);
	Roll(rotationSpeed.x* elapsedTime);
	Pitch(rotationSpeed.y * elapsedTime);
	Yaw(rotationSpeed.z * elapsedTime);



	if (position[3][0] > maxBoundary.x)
	{
		position[3][0] -= 0.1;
		SetMoveDirAndRotate(rand() % 4);
	}
	else if (position[3][0] < minBoundary.x)
	{
		position[3][0] += 0.1;
		SetMoveDirAndRotate(rand() % 4);
	}
	else if (position[3][2] > maxBoundary.z)
	{
		position[3][2] -= 0.1;
		SetMoveDirAndRotate(rand() % 4);
	}
	else if (position[3][2] < minBoundary.z)
	{
		position[3][2] += 0.1;
		SetMoveDirAndRotate(rand() % 4);
	}

	worldMatrix = GetFinalMatrix();
}
