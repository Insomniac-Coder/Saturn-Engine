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
		float MaterialIndex;
	};

	struct DrawInfo {
		glm::vec4 Color;
		float TextureSlots[4];
	};

	enum class BufferType {
		VERTEX,
		DRAWINFO
	};
}

class VertexBuffer
{
private:
	unsigned int vertexBufferId;

public:

	VertexBuffer(std::vector<Saturn::Vertex> data);
	VertexBuffer(unsigned int itemCount);
	~VertexBuffer();
	void Bind();
	void UnBind();
	void AddDataToBuffer(unsigned int offset, std::vector<Saturn::Vertex> vertices);
};

#endif VERTEXBUFFER_H