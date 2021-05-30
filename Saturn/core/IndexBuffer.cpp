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
	glGenBuffers(1, &indexBufferId); //used for buffer generation
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId); // telling opengl which buffer to use by passing the buffer id, also we need to tell what type of buffer this is
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arraySize * sizeof(unsigned int), data, GL_STATIC_DRAW); // populating the buffer with data and telling the size and usage of the buffer
			   //Buffer type,    size of that buffer,   data,  what will be done with that data

	UnBind();
}