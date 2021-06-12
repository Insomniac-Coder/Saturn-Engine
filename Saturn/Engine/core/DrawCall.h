#ifndef DRAWCALL_H
#define DRAWCALL_H

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

namespace Saturn
{
	class DrawCall
	{
	public:
		DrawCall();
		~DrawCall();
		void PushObject(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec4 Color, std::string albedoTexture, std::string normalTexture, std::string ambientTexture, std::string metallicTexture);
		bool IsAccomodationPossible(unsigned int vertexCount, unsigned int textureCount);
		static void SetMaxTextureSlots(const unsigned short& imageUnits);
		inline VertexArray* GetVertexArray() const { return VAO; }
		inline std::vector<DrawInfo> GetDrawInfo() const { return m_DrawInfo; }
		inline std::vector<Texture> GetTextures() const { return d_Textures; }
		inline unsigned long int GetIndicesCount() const { return d_IndicesSize; }
		inline unsigned int GetUsedBufferSize() const { return d_UsedBufferSize; }

	private:
		unsigned int d_UsedBufferSize = 0;
		unsigned short d_UsedTextureSlots = 1;
		static unsigned short d_MaxTextureSlots;
		const unsigned int MAXBUFFERSIZE = 500000 * sizeof(Vertex); //500k max vertices per draw call
		unsigned long int d_MaxIndex = 0;
		unsigned long int d_IndicesSize = 0;
		unsigned int d_ObjectCount = 0;
		unsigned int d_MaterialIndex = 0;

		VertexArray* VAO;
		VertexBuffer* VBO;
		IndexBuffer* IBO;
		std::vector<DrawInfo> m_DrawInfo;
		std::vector<Texture> d_Textures;
	};

}

#endif DRAWCALL_H
