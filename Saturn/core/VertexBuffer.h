#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include "glad/glad.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 BiTangent;
};

class VertexBuffer
{
private:
	unsigned int vertexBufferId;

public:

	VertexBuffer(const Vertex* data, unsigned int arraySize);
	~VertexBuffer();
	void Bind();
	void UnBind();
};

#endif VERTEXBUFFER_H