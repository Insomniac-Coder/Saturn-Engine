#include "VertexBuffer.h"

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