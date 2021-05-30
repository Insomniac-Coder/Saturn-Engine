#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include "glad/glad.h"
#include <string>
#include "TypeName.h"

class VertexBuffer
{
private:
	unsigned int vertexBufferId;
	std::string typeName;

public:
	template <typename T>
	VertexBuffer(const T* data, unsigned int arraySize) : typeName(type_name<T>())
	{
		glGenBuffers(1, &vertexBufferId); //used for buffer generation
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId); // telling opengl which buffer to use by passing the buffer id, also we need to tell what type of buffer this is
		glBufferData(GL_ARRAY_BUFFER, sizeof(T) * arraySize, data, GL_STATIC_DRAW); // populating the buffer with data and telling the size and usage of the buffer
				   //Buffer type,    size of that buffer,   data,  what will be done with that data
		UnBind();
	}
	~VertexBuffer();
	void Bind();
	void UnBind();
	inline std::string GetTypeName() { return typeName; }
};

#endif VERTEXBUFFER_H