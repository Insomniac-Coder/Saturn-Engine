#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "VertexBuffer.h"

class VertexArray
{
private:
	unsigned int vertexArrayId;
	VertexBuffer* vb;
	int pos = 0;
	int offsetSizeVal = 0;
	std::string suppliedType;

public:
	VertexArray(VertexBuffer* vbRef);
	~VertexArray();
	void Bind();
	void UnBind();
	void AddAttribute(int size, int stride);
};

#endif VERTEXARRAY_H