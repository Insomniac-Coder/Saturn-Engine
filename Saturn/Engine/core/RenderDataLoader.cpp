#include "RenderDataLoader.h"
#include "Log/Log.h"

Saturn::RenderDataLoader::RenderDataLoader(const std::string& dataFilePath)
{
    FileLoader(dataFilePath);
    LOG_INFO("Vertex Count: " + std::to_string(m_Vertices.size()));
    LOG_INFO("Index Count" + std::to_string(m_Indices.size()));

    data = new RenderData;
    data->Vertices = m_Vertices;
    data->Indices = m_Indices;
}

Saturn::RenderDataLoader::~RenderDataLoader()
{
    delete data;

}

Saturn::RenderData* Saturn::RenderDataLoader::GetRenderData()
{
	return data;
}

void Saturn::RenderDataLoader::FileLoader(std::string fileName)
{
    std::string output = "";
    std::string line;
    std::string DataType = "";

    std::ifstream iFile(fileName.c_str(), std::ios::in);
    std::vector<glm::vec3> Positions;
    std::vector<glm::vec3> Normals;
    std::vector<glm::vec2> TexCoords;

    if (iFile.good()) {
        while (std::getline(iFile, line)) {
            if (line.find("----POSITIONS----") != std::string::npos) {
                DataType = "POSITION";
            }
            else if (line.find("----NORMALS----") != std::string::npos) {
                DataType = "NORMAL";
            }
            else if (line.find("----TEXCOORDS----") != std::string::npos) {
                DataType = "TEXCOORDS";
            }
            else if (line.find("----INDICES----") != std::string::npos) {
                DataType = "INDICES";
            }

            if (DataType != "") {
                if (DataType == "POSITION" && line.find("----") == std::string::npos) {
                    std::istringstream temp(line);
                    glm::vec3 pos;
                    temp >> pos.x; temp >> pos.y; temp >> pos.z;
                    Positions.push_back(pos);
                }
                else if (DataType == "NORMAL" && line.find("----") == std::string::npos) {
                    std::istringstream temp(line);
                    glm::vec3 norm;
                    temp >> norm.x; temp >> norm.y; temp >> norm.z;
                    Normals.push_back(norm);
                }
                else if (DataType == "TEXCOORDS" && line.find("----") == std::string::npos) {
                    std::istringstream temp(line);
                    glm::vec2 tex;
                    temp >> tex.x; temp >> tex.y;
                    TexCoords.push_back(tex);
                }
                else if (DataType == "INDICES" && line.find("----") == std::string::npos) {
                    std::istringstream temp(line);
                    int ind;
                    temp >> ind;
                    m_Indices.push_back(ind);
                }
            }
        }

        iFile.close();

        for (int i = 0; i < Positions.size(); i++) {
            Vertex vert;
            vert.Position = Positions[i];
            vert.Normal = Normals[i];
            vert.TexCoords = TexCoords[i];
            m_Vertices.push_back(vert);
        }
    }
    else {
        LOG_FAIL("Unable to open file " + fileName);
    }

}
