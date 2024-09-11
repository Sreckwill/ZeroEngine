
#include <vector>
#include <string>
#include "GL/glew.h"	// Important - this header must come before glfw3 header
#include "glm/glm.hpp"
#include "VertexArray.h"
#include "VertexBuffer.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoords;
	glm::vec3 normal;
};

class Mesh
{
public:
	 Mesh();
	~Mesh();
	bool loadOBJ(const std::string& filename);
	void draw();
	VertexArray va;
	VertexBuffer vb;
private:
	void initBuffers();
	bool mLoaded;
	std::vector<Vertex> mVertices;       
};

