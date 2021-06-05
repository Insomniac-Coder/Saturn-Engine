#include "Mesh.h"
#include "Log/Log.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Saturn::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture Albedo, std::string shaderPath) : m_Texture(Albedo), m_Shader(Shader(shaderPath))
{

	m_Vao = new VertexArray();
	m_Vao->Bind();
	m_Vbo = new VertexBuffer(vertices);
	m_Ibo = new IndexBuffer(&indices[0], indices.size());

	for (int i = 0; i < indices.size(); i++) {
		LOG_INFO("Index: " + std::to_string(indices[i]));
	}

	LOG_INFO("Number of vertices: " + std::to_string(vertices.size()));

	for (int i = 0; i < vertices.size(); i++) {
		LOG_INFO("Position: " + std::to_string(vertices[i].Position.x) + ", " + std::to_string(vertices[i].Position.y) + ", " + std::to_string(vertices[i].Position.z));
	}

	for (int i = 0; i < vertices.size(); i++) {
		LOG_INFO("Normals: " + std::to_string(vertices[i].Normal.x) + ", " + std::to_string(vertices[i].Normal.y) + ", " + std::to_string(vertices[i].Normal.z));
	}

	for (int i = 0; i < vertices.size(); i++) {
		LOG_INFO("TexCoord: " + std::to_string(vertices[i].TexCoords.x) + ", " + std::to_string(vertices[i].TexCoords.y));
	}

	m_Vao->AddAttribute(sizeof(((Vertex*)0)->Position) / sizeof(float));
	m_Vao->AddAttribute(sizeof(((Vertex*)0)->Normal) / sizeof(float));
	m_Vao->AddAttribute(sizeof(((Vertex*)0)->TexCoords) / sizeof(float));

	//Unbinding
	m_Vao->UnBind();
	m_Vbo->UnBind();
	m_Ibo->UnBind();


	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)1280 / (float)720, 0.1f, 100.0f);
	glm::mat4 view = glm::mat4(1.0f);
	m_Shader.SetUniform("projection", projection);
	m_Shader.SetUniform("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
	m_Shader.SetUniform("model", model);

	m_Texture.Bind();
	m_Shader.Bind();
	m_Shader.SetUniform("texture_diffuse1", 0);
}

void Saturn::Mesh::Draw()
{
	
	m_Shader.Bind();
	m_Vao->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	m_Vao->UnBind();
	m_Shader.UnBind();
	m_Texture.UnBind();
}
