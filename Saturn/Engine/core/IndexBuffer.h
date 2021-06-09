#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#include "glad/glad.h"
#include <vector>

class IndexBuffer
{
private:
	unsigned int indexBufferId;
	unsigned int count;

public:
	IndexBuffer(const unsigned int* data, unsigned int arraySize);
	IndexBuffer(unsigned int arraySize);
	~IndexBuffer();
	void Bind();
	void UnBind();
	void AddDataToBuffer(unsigned int offset, std::vector<unsigned int> indices);
	inline const unsigned int GetCount() const { return count; }
};

#endif INDEXBUFFER_H