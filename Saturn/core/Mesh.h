#ifndef MESH_H
#define MESH_H

#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <vector>
#include <string>

namespace Saturn {

	class Mesh
	{
	private:
		VertexBuffer* m_Vbo;
		VertexArray* m_Vao;
		IndexBuffer* m_Ibo;
		std::vector<Texture> m_Textures;
		void SetupMesh();

	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		void Draw(Shader& shader);
	};

}

#endif MESH_H