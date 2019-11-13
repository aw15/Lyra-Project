#pragma once
class Renderer;


struct Mesh
{
	vector<glm::vec3> vertex;
	vector<int> index;
	vector<glm::vec3> color;
};

struct ObjectDesc
{
	Mesh mesh;
};

class Object
{
public:
	Object();
	~Object();
	bool Initialize(const ObjectDesc& object);
	void Render(Renderer* const renderer);
	glm::mat4 GetFinalMatrix();
public:
	GLuint  vao;
	GLuint  vbo[2];

	ObjectDesc objectInfo;

	glm::mat4 position{};
	glm::mat4 rotation{};
	glm::mat4 scale{};

	glm::mat4 finalMatrix{};
};

