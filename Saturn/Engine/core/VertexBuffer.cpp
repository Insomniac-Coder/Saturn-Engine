#include "VertexBuffer.h"
#include "Log/Log.h"

VertexBuffer::VertexBuffer(std::vector<Saturn::Vertex> data)
{
	glGenBuffers(1, &vertexBufferId);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Saturn::Vertex) * data.size(), &data[0], GL_STATIC_DRAW);
	//LOG_INFO(std::to_string(sizeof(Saturn::Vertex) * data.size()));
}

VertexBuffer::VertexBuffer(unsigned int itemCount)
{
	glGenBuffers(1, &vertexBufferId);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, itemCount * sizeof(Saturn::Vertex), nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &vertexBufferId);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::AddDataToBuffer(unsigned int offset, std::vector<Saturn::Vertex> vertices)
{
	Bind();
	//void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	//memcpy(ptr, &vertices[0], sizeof(Saturn::Vertex) * vertices.size());
	//glNamedBufferSubData(vertexBufferId, offset * sizeof(Saturn::Vertex), vertices.size() * sizeof(Saturn::Vertex), &vertices[0]);
	//glUnmapBuffer(GL_ARRAY_BUFFER);
	glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Saturn::Vertex), vertices.size() * sizeof(Saturn::Vertex), &vertices[0]);
	UnBind();
}
