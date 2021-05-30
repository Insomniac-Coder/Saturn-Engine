#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#include "glad/glad.h"
#include <string>
#include "TypeName.h"

class IndexBuffer
{
private:
	unsigned int indexBufferId;
	unsigned int count;
	std::string typeName;

public:
	template <typename T>
	IndexBuffer(const T* data, unsigned int arraySize) : count(arraySize), typeName(type_name<T>())
	{
		glGenBuffers(1, &indexBufferId); //used for buffer generation
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId); // telling opengl which buffer to use by passing the buffer id, also we need to tell what type of buffer this is
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, arraySize * sizeof(T), data, GL_STATIC_DRAW); // populating the buffer with data and telling the size and usage of the buffer
				   //Buffer type,    size of that buffer,   data,  what will be done with that data
	}

	~IndexBuffer();
	void Bind();
	void UnBind();
	inline const unsigned int GetCount() const { return count; }
	inline std::string GetTypeName() { return typeName; }
};

#endif INDEXBUFFER_H