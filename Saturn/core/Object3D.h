#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "GameObject.h"
#include "assimp/Importer.hpp""
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Mesh.h"

namespace Saturn {

	class Object3D : public GameObject
	{
	public:
		Object3D(std::string object3DPath, std::string diffuse, std::string specular, std::string normal, std::string height, bool gamma = false);
		void Draw(Shader& shader);


	private:
		std::vector<Texture> o_Textures;
		std::vector<Mesh> o_Meshes;
		std::string o_Directory;
		std::string o_Diffuse, o_Specular, o_Normal, o_Height;
		bool o_GammaCorrection;
		bool o_Active = true;
		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	};

}

#endif OBJECT3D_H