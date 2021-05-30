#include "VertexArray.h"

VertexArray::VertexArray(VertexBuffer* vbRef) : vb(vbRef)
{
	glGenVertexArrays(1, &vertexArrayId);
	Bind();
	vb->Bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vertexArrayId);
}

void VertexArray::Bind()
{
	glBindVertexArray(vertexArrayId);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

void VertexArray::AddAttribute(int size, int stride) {
	GLenum dataType = GL_FLOAT;
	size_t sizeOfType = sizeof(Vertex);

	glVertexAttribPointer(pos, size, dataType, false, stride * sizeOfType, (void*)(offsetSizeVal * sizeOfType)); //telling opengl about various attributes in a vertex
	glEnableVertexAttribArray(pos); // enabling a particular vertex attribute
	pos++;
	offsetSizeVal += size;
}