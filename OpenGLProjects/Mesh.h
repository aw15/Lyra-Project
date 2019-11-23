#pragma once
class Renderer;

enum class MeshType
{
	Cylinder,
	Sphere,
	Obj
};

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
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
	void CreateMeshByObjAsync(const string& path);



	GLuint GetVAO() const { return vao; };

	void Delete();
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

