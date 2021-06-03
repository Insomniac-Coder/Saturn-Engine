#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <string>

std::string ReadFile(std::string fileName);
void WriteFile(std::string fileName, std::string content);
std::string GetValue(std::string fileName, std::string key);
bool IsFilePresent(std::string fileName);

#endif FILEIO_H