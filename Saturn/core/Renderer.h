#ifndef RENDERER_H
#define RENDERER_H

#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include "logging/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

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
		glm::vec4 r_ClearColor = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
	};

}
#endif RENDERER_H

