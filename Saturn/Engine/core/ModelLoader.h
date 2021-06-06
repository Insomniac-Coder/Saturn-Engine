#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Log/Log.h"
#include <vector>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <fstream>

namespace Saturn {

	struct Mesh {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		unsigned int maxIndexVal;
	};

	class ModelLoader
	{
	private:
		std::string path;
		std::vector<Mesh> meshes;
	public:
		ModelLoader(std::string object3DPath);
	};

}

#endif MODELLOADER_H