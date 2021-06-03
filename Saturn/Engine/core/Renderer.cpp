#include "Renderer.h"
#include "FileIO.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "ModelLoader.h"

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
	LOG_INFO((char*)glGetString(GL_VERSION));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

Saturn::Renderer::~Renderer()
{
}

void Saturn::Renderer::Run()
{

	/*
	std::vector<Vertex> vertices = {
						{
							{-0.5f, -0.5f, 0.0f},
							{0.0f, 0.0f, 0.0f},
							{0.0f, 0.0f}
						},
						{
							{0.5f, -0.5f, 0.0f},
							{0.0f, 0.0f, 0.0f},
							{1.0f, 0.0f}
						},
						{
							{0.5f,  0.5f, 0.0f},
							{0.0f, 0.0f, 0.0f},
							{1.0f, 1.0f}
						},
						{
							{-0.5f,  0.5f, 0.0f},
							{0.0f, 0.0f, 0.0f},
							{0.0f, 1.0f}
						}
	};

	std::vector<unsigned int> indices = {	//for index buffer
		0, 1, 2,
		2, 3, 0
	};

	VertexArray * va = new VertexArray();
	va->Bind();
	VertexBuffer * vb = new VertexBuffer(vertices);
	IndexBuffer * ib = new IndexBuffer(&indices[0], 6);

	va->AddAttribute(sizeof(((Vertex*)0)->Position) / sizeof(float));
	va->AddAttribute(sizeof(((Vertex*)0)->Normal) / sizeof(float));
	va->AddAttribute(sizeof(((Vertex*)0)->TexCoords) / sizeof(float));

	//Unbiding
	va->UnBind();
	vb->UnBind();
	ib->UnBind();

	std::string filepath = "./Shaders/basic_shader.shader";
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)r_Width / (float)r_Height, 0.1f, 100.0f);
	glm::mat4 projection = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f);

	Shader shader(filepath);

	Texture texture("./Textures/sadpepe.png");
	texture.Bind();

	shader.Bind();
	shader.SetUniform("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetUniform("textureIn", 0);
	shader.SetUniform("projection", projection);
	*/

	
	Shader shader2();

	

	ModelLoader myObj("./3DObjects/cube.obj", "./Textures/sadpepe.png", "./Shaders/3DShader.shader");
	

	LOG_INFO(std::to_string(glGetError()));

	while (!glfwWindowShouldClose(r_Window)) {
		glfwPollEvents();
		glClearColor(r_ClearColor.r, r_ClearColor.g, r_ClearColor.b, r_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//shader.Bind();
		//va->Bind();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		//shader.UnBind();
		//va->UnBind();
		myObj.Draw();

		glfwSwapBuffers(r_Window);
		glfwGetWindowSize(r_Window, &r_Width, &r_Height);
	}

	std::string fileContent = "WindowWidth : " + std::to_string(r_Width) + "\n" + "WindowHeight : " + std::to_string(r_Height) + "\n" + "VirtualRenderWidth : " + std::to_string(r_VirtualWidth) + "\n" + "VirtualRenderHeight : " + std::to_string(r_VirtualHeight) + "\n";
	WriteFile("Config.Saturn", fileContent);
	LOG_PASS("Latest file config saved!");
	LOG_PASS("DEBUG Content:\n" + fileContent);
}
