#include "VertexArray.h"
#include "logging/Log.h"

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

void VertexArray::AddAttribute(int size) {
	size_t sizeOfType = sizeof(Vertex);
	glEnableVertexAttribArray(pos); // enabling a particular vertex attribute
	glVertexAttribPointer(pos, size, GL_FLOAT, false, sizeOfType, (void*)(offsetSizeVal * sizeof(float))); //telling opengl about various attributes in a vertex
	//LOG_INFO("glEnableVertexAttribArray(" + std::to_string(pos) + ")" + "\nglVertexAttribPointer(" + std::to_string(pos) + ", " + std::to_string(size) + ", GL_FLOAT, false, " + std::to_string(sizeOfType) + ", " + std::to_string(offsetSizeVal * sizeof(float)) + ")");
	pos++;
	offsetSizeVal += size;
}