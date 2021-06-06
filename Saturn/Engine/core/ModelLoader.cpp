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
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
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

		unsigned int maxVal = 0;

		for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
			const aiFace* face = &mesh->mFaces[j];
			for (unsigned int k = 0; k < face->mNumIndices; k++) {
				if (face->mIndices[k] > maxVal)
					maxVal = face->mIndices[k];
				indices.push_back(face->mIndices[k]);
			}
		}
		LOG_INFO("Number of Indices: " + std::to_string(indices.size()));
		LOG_INFO("Max value: " + std::to_string(maxVal));

		meshes.push_back({ vertices, indices, maxVal });
	}


	//Create Data file
	std::string posinfo = "----POSITIONS----\n";
	std::string norminfo = "----NORMALS----\n";
	std::string texinfo = "----TEXCOORDS----\n";
	std::string indinfo = "----INDICES----\n";

	unsigned int shiftVal = 0;

	for (int x = 0; x < meshes.size(); x++) {

		for (int i = 0; i < meshes[x].vertices.size(); i++)
		{
			posinfo += (std::to_string(meshes[x].vertices[i].Position.x) + " " + std::to_string(meshes[x].vertices[i].Position.y) + " " + std::to_string(meshes[x].vertices[i].Position.z) + "\n");
			norminfo += (std::to_string(meshes[x].vertices[i].Normal.x) + " " + std::to_string(meshes[x].vertices[i].Normal.y) + " " + std::to_string(meshes[x].vertices[i].Normal.z) + "\n");
			texinfo += (std::to_string(meshes[x].vertices[i].TexCoords.x) + " " + std::to_string(meshes[x].vertices[i].TexCoords.y) + "\n");
		}

		for (int i = 0; i < meshes[x].indices.size(); i++)
		{
			if(x != 0)
				indinfo += (std::to_string(meshes[x].indices[i] + shiftVal) + "\n");
			else
				indinfo += (std::to_string(meshes[x].indices[i]) + "\n");
		}
		shiftVal += meshes[x].maxIndexVal;
	}

	std::ofstream oFile("./RenderData/object.data", std::ios::out );
	posinfo = posinfo + norminfo + texinfo + indinfo;
	oFile << posinfo;
	oFile.close();
}

