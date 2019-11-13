#pragma once
class Renderer;
	

class BasicObject
{
public:
	BasicObject();
	~BasicObject();
	bool Initialize(const BasicObjectDesc& desc, Renderer* renderer);
	bool Initialize(const BasicObjectDesc& desc, Renderer* renderer, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	void Render();
	void Update(const double elapsedTime);
	glm::mat4 GetFinalMatrix();

private:
	GLuint primitiveType = GLU_LINE;//어떤 프리미티브로 그릴건지
	BasicShapeType basicType = BasicShapeType::SPHERE;

	glm::mat4 position = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 finalMatrix = glm::mat4(1.0f);

	Renderer* renderer = nullptr;
};

