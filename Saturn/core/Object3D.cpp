#include "Object3D.h"
#include "logging/Log.h"

Saturn::Object3D::Object3D(std::string object3DPath, std::string diffuse, std::string specular, std::string normal, std::string height, bool gamma) : o_GammaCorrection(gamma), o_Diffuse(diffuse), o_Specular(specular), o_Normal(normal), o_Height(height)
{
	loadModel(object3DPath);
}

void Saturn::Object3D::Draw(Shader& shader)
{
	if (o_Active) {
		for (int i = 0; i < o_Meshes.size(); i++) {
			o_Meshes[i].Draw(shader);
		}
	}
}

void Saturn::Object3D::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG_FAIL("ERROR::ASSIMP:: " + (std::string)importer.GetErrorString());
		return;
	}

    LOG_INFO("Number of meshes" + std::to_string(scene->mNumMeshes));
    processScene(scene);

}

void Saturn::Object3D::processScene(const aiScene* scene)
{
	bool load = true;

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
					// tangent
					vector.x = mesh->mTangents[j].x;
					vector.y = mesh->mTangents[j].y;
					vector.z = mesh->mTangents[j].z;
					vert.Tangent = vector;
					// bitangent
					vector.x = mesh->mBitangents[j].x;
					vector.y = mesh->mBitangents[j].y;
					vector.z = mesh->mBitangents[j].z;
					vert.BiTangent = vector;
				}
				else {
					vert.TexCoords = glm::vec2(0.0f);
					vert.Tangent = glm::vec3(0.0f);
					vert.BiTangent = glm::vec3(0.0f);
				}
				LOG_INFO("\n" + std::to_string(vert.Position.x) + ", " + std::to_string(vert.Position.y) + ", " + std::to_string(vert.Position.z));
				vertices.push_back(vert);
			}
		}

		for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
			const aiFace* face = &mesh->mFaces[j];
			for (unsigned int k = 0; k < face->mNumIndices; k++) {
				indices.push_back(face->mIndices[k]);
			}
		}

		if (load) {
			tex.push_back(Texture(o_Diffuse, "texture_diffuse"));
			load = false;
		}
		o_Meshes.push_back(Mesh(vertices, indices, tex));
	}
}
