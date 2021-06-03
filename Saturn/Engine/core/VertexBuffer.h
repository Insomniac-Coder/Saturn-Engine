#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <vector>

namespace Saturn {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
}

class VertexBuffer
{
private:
	unsigned int vertexBufferId;

public:

	VertexBuffer(std::vector<Saturn::Vertex> data);
	~VertexBuffer();
	void Bind();
	void UnBind();
};

#endif VERTEXBUFFER_H