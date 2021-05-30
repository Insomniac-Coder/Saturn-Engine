#include "VertexArray.h"

VertexArray::VertexArray(VertexBuffer* vbRef) : vb(vbRef)
{
	suppliedType = vb->GetTypeName();
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
	GLenum dataType = 0;
	size_t sizeOfType = 0;
	if (suppliedType == "int") {
		dataType = GL_INT;
		sizeOfType = sizeof(int);
	}
	else if (suppliedType == "unsigned int") {
		dataType = GL_UNSIGNED_INT;
		sizeOfType = sizeof(unsigned int);
	}
	else if (suppliedType == "float") {
		dataType = GL_FLOAT;
		sizeOfType = sizeof(float);
	}
	else if (suppliedType == "double") {
		dataType = GL_DOUBLE;
		sizeOfType = sizeof(double);
	}

	glVertexAttribPointer(pos, size, dataType, false, stride * sizeOfType, (void*)(offsetSizeVal * sizeOfType)); //telling opengl about various attributes in a vertex
	glEnableVertexAttribArray(pos); // enabling a particular vertex attribute
	pos++;
	offsetSizeVal += size;
}