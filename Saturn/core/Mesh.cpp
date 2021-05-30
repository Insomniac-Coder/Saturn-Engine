#include "Mesh.h"

Saturn::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : m_Textures(textures){
	m_Vbo = new VertexBuffer(&vertices[0], vertices.size());
	m_Vao = new VertexArray(m_Vbo);
    m_Vbo->Bind();

	SetupMesh();

	m_Ibo = new IndexBuffer(&indices[0], indices.size());

	m_Vao->UnBind();
	m_Vbo->UnBind();
	m_Ibo->UnBind();

}

void Saturn::Mesh::Draw(Shader& shader) {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

   

    for (int i = 0; i < m_Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = m_Textures[i].GetType();
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        shader.SetUniform((name + number).c_str(), i);
        m_Textures[i].Bind();
    }

    shader.Bind();
    m_Vao->Bind();
    m_Ibo->Bind();
    glDrawElements(GL_TRIANGLES, m_Ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
    
    shader.UnBind();
    m_Vao->UnBind();
    m_Ibo->UnBind();

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Saturn::Mesh::SetupMesh() {
	m_Vao->AddAttribute(sizeof(((Vertex*)0)->Position), sizeof(Vertex));
	m_Vao->AddAttribute(sizeof(((Vertex*)0)->Normal), sizeof(Vertex));
	m_Vao->AddAttribute(sizeof(((Vertex*)0)->TexCoords), sizeof(Vertex));
	m_Vao->AddAttribute(sizeof(((Vertex*)0)->Tangent), sizeof(Vertex));
	m_Vao->AddAttribute(sizeof(((Vertex*)0)->BiTangent), sizeof(Vertex));
}