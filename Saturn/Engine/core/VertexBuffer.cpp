#include "VertexBuffer.h"
#include "Log/Log.h"

VertexBuffer::VertexBuffer(std::vector<Saturn::Vertex> data)
{
	glGenBuffers(1, &vertexBufferId);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Saturn::Vertex) * data.size(), &data[0], GL_STATIC_DRAW);
	//LOG_INFO(std::to_string(sizeof(Saturn::Vertex) * data.size()));
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