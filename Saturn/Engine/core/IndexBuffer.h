#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#include "glad/glad.h"

class IndexBuffer
{
private:
	unsigned int indexBufferId;
	unsigned int count;

public:
	IndexBuffer(const unsigned int* data, unsigned int arraySize);
	~IndexBuffer();
	void Bind();
	void UnBind();
	inline const unsigned int GetCount() const { return count; }
};

#endif INDEXBUFFER_H