#include "DrawCall.h"
#include "Log/Log.h"

unsigned short Saturn::DrawCall::d_MaxTextureSlots;

Saturn::DrawCall::DrawCall()
{
	VAO = new VertexArray();
	VAO->Bind();

	VBO = new VertexBuffer(MAXBUFFERSIZE / sizeof(Vertex));
	IBO = new IndexBuffer((MAXBUFFERSIZE / sizeof(Vertex)) * 5);
	
	VAO->AddAttribute(sizeof(((Vertex*)0)->Position) / sizeof(float));
	VAO->AddAttribute(sizeof(((Vertex*)0)->Normal) / sizeof(float));
	VAO->AddAttribute(sizeof(((Vertex*)0)->TexCoords) / sizeof(float));
	VAO->AddAttribute(sizeof(((Vertex*)0)->MaterialIndex) / sizeof(float));

	VAO->UnBind();
	VBO->UnBind();
	IBO->UnBind();
}

Saturn::DrawCall::~DrawCall()
{
	delete VAO, VBO, IBO;
}

void Saturn::DrawCall::PushObject(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec4 Color, std::string albedoTexture, std::string normalTexture, std::string ambientTexture, std::string metallicTexture)
{

	if (d_IndicesSize == 0) {
		VBO->AddDataToBuffer(0 + (d_UsedBufferSize / sizeof(Vertex)), vertices);
		for (int i = 0; i < indices.size(); i++) {
			if (d_MaxIndex < indices[i]) {
				d_MaxIndex = indices[i];
			}
		}
		IBO->AddDataToBuffer(0 + d_IndicesSize, indices);
		d_MaterialIndex++;
	}
	else
	{
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].MaterialIndex = d_MaterialIndex;
			//LOG_INFO("Info value being used is " + std::to_string(d_MaterialIndex));
		}
		VBO->AddDataToBuffer(0 + (d_UsedBufferSize / sizeof(Vertex)), vertices);

		int tempVal = 0;

		for (int i = 0; i < indices.size(); i++) {
			indices[i] += (d_MaxIndex + 1);

			if (tempVal < indices[i])
			{
				tempVal = indices[i];
			}
		}

		d_MaxIndex = tempVal;
		IBO->AddDataToBuffer(0 + d_IndicesSize, indices);
		d_MaterialIndex++;
	}

	d_IndicesSize += indices.size();

	DrawInfo dInfo;

	dInfo.Color = Color;

	if (albedoTexture != "") {
		dInfo.TextureSlots[0] = d_UsedTextureSlots++;
		d_Textures.push_back(Texture(albedoTexture));
	}
	else
	{
		dInfo.TextureSlots[0] = 0;
	}

	if (normalTexture != "") {
		dInfo.TextureSlots[1] = d_UsedTextureSlots++;
		d_Textures.push_back(Texture(albedoTexture));
	}
	else
	{
		dInfo.TextureSlots[1] = 0;
	}

	if (ambientTexture != "") {
		dInfo.TextureSlots[2] = d_UsedTextureSlots++;
		d_Textures.push_back(Texture(albedoTexture));
	}
	else
	{
		dInfo.TextureSlots[2] = 0;
	}

	if (metallicTexture != "") {
		dInfo.TextureSlots[3] = d_UsedTextureSlots++;
		d_Textures.push_back(Texture(albedoTexture));
	}
	else
	{
		dInfo.TextureSlots[3] = 0;
	}

	m_DrawInfo.push_back(dInfo);

	d_UsedBufferSize += (vertices.size() * sizeof(Vertex));

}

bool Saturn::DrawCall::IsAccomodationPossible(unsigned int vertexCount, unsigned int textureCount)
{
	return (((sizeof(Saturn::Vertex) * vertexCount) < (MAXBUFFERSIZE - d_UsedBufferSize)) && ((d_MaxTextureSlots - d_UsedTextureSlots) > textureCount)) ? true : false;
}

void Saturn::DrawCall::SetMaxTextureSlots(const unsigned short& imageUnits)
{
	d_MaxTextureSlots = imageUnits;
}
