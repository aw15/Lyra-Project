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
	void CreateMeshByVertices(const vector<glm::vec3>& vertices, const vector<glm::vec3>& colors);

	GLuint GetVAO() const { return vao; };

	void Delete();
public:
	int size = 0;
	vector<glm::vec3> vertices;
private:
	vector<int> index;
	vector<glm::vec3> colors;

	GLuint  vao = UINT_MAX;
	GLuint  vbo[2] = {0,0};

	MeshType type;
};

