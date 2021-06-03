#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &indexBufferId);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int arraySize) : count(arraySize)
{
	glGenBuffers(1, &indexBufferId);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arraySize * sizeof(unsigned int), data, GL_STATIC_DRAW);
}