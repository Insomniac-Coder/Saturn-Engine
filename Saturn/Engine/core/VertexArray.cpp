#include "VertexArray.h"
#include "Log/Log.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vertexArrayId);
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
	glEnableVertexAttribArray(pos); // enabling a particular vertex attribute
	glVertexAttribPointer(pos, size, GL_FLOAT, false, sizeof(Saturn::Vertex), (void*)(offsetSizeVal * sizeof(float))); //telling opengl about various attributes in a vertex
	LOG_INFO("glEnableVertexAttribArray(" + std::to_string(pos) + ")" + "\nglVertexAttribPointer(" + std::to_string(pos) + ", " + std::to_string(size) + ", GL_FLOAT, false, " + std::to_string(sizeof(Saturn::Vertex)) + ", " + std::to_string(offsetSizeVal * sizeof(float)) + ")");
	pos++;
	offsetSizeVal += size;
}