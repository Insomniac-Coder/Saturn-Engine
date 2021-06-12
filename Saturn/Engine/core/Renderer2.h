#ifndef RENDERER_H
#define RENDERER_H
#include "Log/Log.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "Shader.h"
#include "Texture.h"
#include "RenderDataLoader.h"
#include "ModelLoader.h"
#include "../Editor/UIElement.h"
#include "FileIO.h"
#include "Camera.h"
#include "DrawCall.h"

namespace Saturn {

	class Renderer
	{
	public:
		Renderer(unsigned int windowWidth, unsigned int windowHeight, unsigned int virtualWidth, unsigned int virtualHeight, GLFWwindow* windowRef);
		~Renderer();
		void Run();

	private:
		GLFWwindow* r_Window;
		int r_Width;
		int r_Height;
		int r_VirtualWidth;
		int r_VirtualHeight;
		glm::vec4 r_ClearColor = glm::vec4(0.05f, 0.05f, 0.05f, 1.0f);
		VertexArray* r_ObjectVao;
		Texture* defaultTexture;
	};

}
#endif RENDERER_H

