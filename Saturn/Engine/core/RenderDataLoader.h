#ifndef RENDERDATALOADER_H
#define RENDERDATALOADER_H

#include "VertexArray.h"
#include "IndexBuffer.h"
#include <string>
#include <sstream>
#include <fstream>

namespace Saturn {

	struct RenderData {
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;
	};

	class RenderDataLoader {
	public:
		RenderDataLoader(const std::string& dataFilePath);
		~RenderDataLoader();
		RenderData* GetRenderData();

	private:
		void FileLoader(std::string fileName);
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		RenderData* data;
	};

}

#endif RENDERDATALOADER_H
