#include "ModelLoader.h"

Saturn::ModelLoader::ModelLoader(std::string object3DPath): path(object3DPath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG_FAIL("ERROR::ASSIMP:: " + (std::string)importer.GetErrorString());
		return;
	}

	LOG_INFO("Number of meshes: " + std::to_string(scene->mNumMeshes));
	
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{

		glm::vec3 vector;
		// process each mesh located at the current node
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

			LOG_INFO("Number of vertices: " + std::to_string(mesh->mNumVertices));
		}

		for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
			const aiFace* face = &mesh->mFaces[j];
			for (unsigned int k = 0; k < face->mNumIndices; k++) {
				indices.push_back(face->mIndices[k]);
			}
		}
	}

	LOG_INFO("Vertices Count: " + std::to_string(vertices.size()));
	LOG_INFO("Indices Count: " + std::to_string(indices.size()));

	//Create Data file
	std::string posinfo = "----POSITIONS----\n";
	std::string norminfo = "----NORMALS----\n";
	std::string texinfo = "----TEXCOORDS----\n";
	std::string indinfo = "----INDICES----\n";

	for (int i = 0; i < vertices.size(); i++)
	{
		posinfo += (std::to_string(vertices[i].Position.x) + " " + std::to_string(vertices[i].Position.y) + " " + std::to_string(vertices[i].Position.z) + "\n");
		norminfo += (std::to_string(vertices[i].Normal.x) + " " + std::to_string(vertices[i].Normal.y) + " " + std::to_string(vertices[i].Normal.z) + "\n");
		texinfo += (std::to_string(vertices[i].TexCoords.x) + " " + std::to_string(vertices[i].TexCoords.y) + "\n");
	}

	for (int i = 0; i < indices.size(); i++)
	{
		indinfo += (std::to_string(indices[i]) + "\n");
	}

	std::ofstream oFile("./RenderData/object.data", std::ios::out );
	posinfo = posinfo + norminfo + texinfo + indinfo;
	oFile << posinfo;
	oFile.close();
}

