#ifndef  TEXTURE_H
#define TEXTURE_H
#include <string>
#include "glad/glad.h"
#include "thirdparty/stb_image.h"

class Texture
{
private:
	unsigned int textureId;
	int width;
	int height;
	int bpp;
	unsigned char* localBuffer;
	std::string file;

public:
	Texture(std::string filePath);
	~Texture();
	void Bind(unsigned int slot = 0);
	void UnBind();
	inline unsigned int GetWidth() { return width; }
	inline unsigned int GetHeight() { return height; }
};

#endif TEXTURE_H
