#include "FileIO.h"

std::string ReadFile(std::string fileName) {
    std::string output = "";
    std::string line;

    std::ifstream iFile(fileName.c_str(), std::ios::in | std::ios::binary);

    if (iFile.good()) {
        while (std::getline(iFile, line)) {
            output += (line + "\n");
        }

        iFile.close();
    }

    return (output == "") ? "No File Found" : output;
}

void WriteFile(std::string fileName, std::string content) {
    std::ofstream oFile(fileName.c_str(), std::ios::out | std::ios::binary);

    oFile << content;

    oFile.close();
}

std::string GetValue(std::string fileName, std::string key) {
    std::string line;
    bool varFound = false;

    std::ifstream iFile(fileName.c_str(), std::ios::in | std::ios::binary);

    if (iFile.good()) {
        while (std::getline(iFile, line)) {
            if (line.rfind(key + " : ") != std::string::npos) {
                varFound = true;
                break;
            }
        }

        iFile.close();
    }

    return (varFound == true) ? line.erase(0, (key + " : ").length()) : "None";
}

bool IsFilePresent(std::string fileName) {
    std::ifstream iFile(fileName.c_str(), std::ios::in | std::ios::binary);

    if (iFile.good())
    {
        return true;
    }
    else
    {
        return false;
    }

}