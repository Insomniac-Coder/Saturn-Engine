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

IndexBuffer::IndexBuffer(unsigned int arraySize) : count(arraySize)
{
	glGenBuffers(1, &indexBufferId);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arraySize * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);
}

void IndexBuffer::AddDataToBuffer(unsigned int offset, std::vector<unsigned int> indices)
{
	Bind();
	//glNamedBufferSubData(indexBufferId, offset * sizeof(unsigned int), indices.size(), &indices[0]);
	//void* ptr = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	//memcpy(ptr, &indices[0], sizeof(unsigned int) * indices.size());
	//glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(unsigned int), indices.size() * sizeof(unsigned int), &indices[0]);
	UnBind();
}