#ifndef RENDERER_H
#define RENDERER_H

#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include "Log/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "Shader.h"
#include "Texture.h"
#include "RenderDataLoader.h"
#include "ModelLoader.h"

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
		glm::vec4 r_ClearColor = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f);
		VertexArray* r_Vao;
		VertexBuffer* r_Vbo;
		IndexBuffer* r_Ibo;
	};

}
#endif RENDERER_H

