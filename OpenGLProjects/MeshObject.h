#pragma once
class Renderer;
class Mesh;

class MeshObject
{
public:
	MeshObject();
	~MeshObject();
	bool Initialize(const BasicObjectDesc& desc, Renderer* renderer, Mesh* mesh);
	bool Initialize(const BasicObjectDesc& desc, Renderer* renderer, Mesh* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	bool Initialize(const BasicObjectDesc& desc, Renderer* renderer, Mesh* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 movementSpeed);
	void Render();
	void Update(const float elapsedTime);

	glm::mat4 GetRevolveFinalMatrix() { return rotation * position * scale; };

	glm::mat4 GetFinalMatrix() { return position * rotation * scale; }

	void Roll(float angle) { currentAngle.x += angle; rotation = glm::rotate(rotation, glm::radians(angle), { 1,0,0 }); }

	void Pitch(float angle) { currentAngle.y += angle; rotation = glm::rotate(rotation, glm::radians(angle), { 0,1,0 }); }

	void Yaw(float angle) { currentAngle.z += angle; rotation = glm::rotate(rotation, glm::radians(angle), { 0,0,1 }); }

	void Translate(glm::vec3 amount) { position = glm::translate(position, amount); }

	void SetRotationSpeed(const glm::vec3 rotationSpeed) { this->rotationSpeed = rotationSpeed; }
	void SetMovementSpeed(const glm::vec3& movementSpeed) { this->movementSpeed = movementSpeed; }


	glm::vec3 GetPosition() { return { position[3][0],position[3][1] , position[3][2] }; }

	void ResetRotation() { rotation = glm::mat4(1.0f); }

public:
	Mesh* mesh = nullptr;
	glm::mat4 worldMatrix = glm::mat4(1.0f);
	bool isActive = true;
	glm::vec3 currentAngle = glm::vec3(0, 0, 0);
	glm::vec3 rotationSpeed = glm::vec3(0, 0, 0);
private:
	GLuint primitiveType = GLU_LINE;//어떤 프리미티브로 그릴건지
	BasicShapeType basicType = BasicShapeType::SPHERE;
	glm::vec3 movementSpeed = glm::vec3(0, 0, 0);

	glm::mat4 position = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);

	Renderer* renderer = nullptr;

};

