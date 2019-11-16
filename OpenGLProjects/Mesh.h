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
	void CreateCube();
	void CreatePyramid();
	void CreateTriangle();
	void CreateRectangle();

	GLuint GetVAO() const { return vao; };
public:
	int size = 0;

private:

	vector<glm::vec3> vertex;
	vector<int> index;
	vector<glm::vec3> color;

	GLuint  vao;
	GLuint  vbo[2];

	MeshType type;
};

