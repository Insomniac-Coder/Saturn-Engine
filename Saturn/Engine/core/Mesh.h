#ifndef MESH_H
#define MESH_H

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

namespace Saturn {

	class Mesh
	{
	private:
		VertexArray* m_Vao;
		VertexBuffer* m_Vbo;
		IndexBuffer* m_Ibo;
		Texture m_Texture;
		Shader m_Shader;
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture Albedo, std::string shaderPath);
		void Draw();
	};

}

#endif MESH_H