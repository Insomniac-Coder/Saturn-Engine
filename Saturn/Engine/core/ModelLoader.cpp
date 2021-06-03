#include "ModelLoader.h"

Saturn::ModelLoader::ModelLoader(std::string object3DPath, std::string albedoPath, std::string shaderPath) : path(object3DPath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG_FAIL("ERROR::ASSIMP:: " + (std::string)importer.GetErrorString());
		return;
	}

	LOG_INFO("Number of meshes: " + std::to_string(scene->mNumMeshes));

	m_Albedo = new Texture(albedoPath);
	
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{

		glm::vec3 vector;
		// process each mesh located at the current node
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		Vertex vert;

		aiMesh* mesh = scene->mMeshes[i];
		if (mesh->HasPositions()) {
			for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
				vector.x = mesh->mVertices[j].x;
				vector.y = mesh->mVertices[j].y;
				vector.z = mesh->mVertices[j].z;
				vert.Position = vector;
				if (mesh->HasNormals()) {
					vector.x = mesh->mNormals[j].x;
					vector.y = mesh->mNormals[j].y;
					vector.z = mesh->mNormals[j].z;
					vert.Normal = vector;
				}
				else {
					vert.Normal = glm::vec3(0.0f);
				}
				if (mesh->HasTextureCoords(0)) {
					vector.x = mesh->mTextureCoords[0][j].x;
					vector.y = mesh->mTextureCoords[0][j].y;
					vert.TexCoords = vector;
				}
				else {
					vert.TexCoords = glm::vec2(0.0f);
				}
				//LOG_INFO("\n" + std::to_string(vert.Position.x) + ", " + std::to_string(vert.Position.y) + ", " + std::to_string(vert.Position.z));
				vertices.push_back(vert);
			}
		}

		for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
			const aiFace* face = &mesh->mFaces[j];
			for (unsigned int k = 0; k < face->mNumIndices; k++) {
				indices.push_back(face->mIndices[k]);
			}
		}

		m_Mesh.push_back(Mesh(vertices, indices, *m_Albedo, shaderPath));
	}
}

void Saturn::ModelLoader::Draw()
{
	for (int i = 0; i < m_Mesh.size(); i++) {
		m_Mesh[i].Draw();
	}
}
