#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "glad/glad.h"
#include "VertexBuffer.h"

class VertexArray
{
private:
	unsigned int vertexArrayId;
	int pos = 0;
	int offsetSizeVal = 0;

public:
	VertexArray();
	~VertexArray();
	void Bind();
	void UnBind();
	void AddAttribute(int size);
};

#endif VERTEXARRAY_H