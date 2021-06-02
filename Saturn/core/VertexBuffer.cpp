#include "VertexBuffer.h"
#include "logging/Log.h"

VertexBuffer::VertexBuffer(const Vertex* data, unsigned int arraySize)
{
	glGenBuffers(1, &vertexBufferId); //used for buffer generation
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId); // telling opengl which buffer to use by passing the buffer id, also we need to tell what type of buffer this is
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * arraySize, data, GL_STATIC_DRAW); // populating the buffer with data and telling the size and usage of the buffer
			   //Buffer type,    size of that buffer,   data,  what will be done with that data
	LOG_INFO(std::to_string(sizeof(Vertex) * arraySize));
	UnBind();
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