#pragma once
class Renderer;

enum class MeshType
{
	Cylinder,
	Sphere,
	Obj
};

class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;
	void Render(Renderer* const renderer);
	void CreateBasicObject(MeshType type);

public:

	vector<glm::vec3> vertex;
	vector<int> index;
	vector<glm::vec3> color;

	GLuint  vao;
	GLuint  vbo[2];

	MeshType type;
};

