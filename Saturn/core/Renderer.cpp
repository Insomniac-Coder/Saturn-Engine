#include "Renderer.h"
#include "FileIO.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

static void WindowResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Saturn::Renderer::Renderer(unsigned int windowWidth, unsigned int windowHeight, unsigned int virtualWidth, unsigned int virtualHeight, GLFWwindow* windowRef) : r_Width(windowWidth), r_Height(windowHeight), r_VirtualWidth(virtualWidth), r_VirtualHeight(virtualHeight), r_Window(windowRef)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(r_Window);
	glfwSetWindowSizeCallback(r_Window, WindowResize);

	gladLoadGL();
	LOG_INFO((char *)glGetString(GL_VERSION));
}

Saturn::Renderer::~Renderer()
{
}

void Saturn::Renderer::Run()
{

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,	//0
		 0.5f, -0.5f, 1.0f, 0.0f,	//1
		 0.5f,  0.5f, 1.0f, 1.0f,	//2
		-0.5f,  0.5f, 0.0f, 1.0f	//3
	};

	unsigned int indices[] = {	//for index buffer
		0, 1, 2,
		2, 3, 0
	};

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glm::mat4 projection = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f);

	VertexBuffer vb(vertices, 16);

	VertexArray va(&vb);

	va.AddAttribute(2, 4);
	va.AddAttribute(2, 4);

	IndexBuffer ib(indices, 6);

	//Unbiding
	va.UnBind();
	vb.UnBind();
	ib.UnBind();

	std::string filepath = "./basic.shader";

	Shader shader(filepath);
	//shader.SetUniform("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

	Texture texture("./sadpepe.png");
	texture.Bind();
	shader.SetUniform("textureIn", 0);
	shader.SetUniform("projection", projection);

	while (!glfwWindowShouldClose(r_Window)) {
		glfwPollEvents();
		glClearColor(r_ClearColor.r, r_ClearColor.g, r_ClearColor.b, r_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();
		va.Bind();
		ib.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(r_Window);
		glfwGetWindowSize(r_Window, &r_Width, &r_Height);
	}

	std::string fileContent = "WindowWidth : " + std::to_string(r_Width) + "\n" + "WindowHeight : " + std::to_string(r_Height) + "\n" + "VirtualRenderWidth : " + std::to_string(r_VirtualWidth) + "\n" + "VirtualRenderHeight : " + std::to_string(r_VirtualHeight) + "\n";
	WriteFile("Config.Saturn", fileContent);
	LOG_PASS("Ltest file config saved!");
	LOG_PASS("DEBUG Content:\n" + fileContent);
}
