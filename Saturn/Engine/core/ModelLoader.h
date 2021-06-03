#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Log/Log.h"
#include "Mesh.h"

namespace Saturn {

	class ModelLoader
	{
	private:
		std::string path;
		std::vector<Mesh> m_Mesh;
		Texture* m_Albedo;
	public:
		ModelLoader(std::string object3DPath, std::string albedoPath, std::string shaderPath);
		void Draw();
	};

}

#endif MODELLOADER_H