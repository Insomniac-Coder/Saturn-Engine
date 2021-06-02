#include "Renderer.h"
#include "FileIO.h"
#include "Object3D.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

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
	Vertex vertices[] = {
							{
								{-0.5f, -0.5f, 0.0f},
								{0.0f, 0.0f, 0.0f},
								{0.0f, 0.0f},
								{0.0f, 0.0f, 0.0f},
								{0.0f, 0.0f, 0.0f}
							},
							{
								{0.5f, -0.5f, 0.0f},
								{0.0f, 0.0f, 0.0f},
								{1.0f, 0.0f},
								{0.0f, 0.0f, 0.0f},
								{0.0f, 0.0f, 0.0f}
							},
							{
								{0.5f,  0.5f, 0.0f},
								{0.0f, 0.0f, 0.0f},
								{1.0f, 1.0f},
								{0.0f, 0.0f, 0.0f},
								{0.0f, 0.0f, 0.0f}
							},
							{
								{-0.5f,  0.5f, 0.0f},
								{0.0f, 0.0f, 0.0f},
								{0.0f, 1.0f},
								{0.0f, 0.0f, 0.0f},
								{0.0f, 0.0f, 0.0f}
							}
	};

	unsigned int indices[] = {	//for index buffer
		0, 1, 2,
		2, 3, 0
	};


	VertexBuffer vb(vertices, 4);

	VertexArray va(&vb);

	IndexBuffer ib(indices, 6);

	va.AddAttribute(sizeof(((Vertex*)0)->Position) / sizeof(float));

	va.AddAttribute(sizeof(((Vertex*)0)->Normal) / sizeof(float));

	va.AddAttribute(sizeof(((Vertex*)0)->TexCoords) / sizeof(float));

	va.AddAttribute(sizeof(((Vertex*)0)->Tangent) / sizeof(float));

	va.AddAttribute(sizeof(((Vertex*)0)->BiTangent) / sizeof(float));

	//Unbiding
	va.UnBind();
	vb.UnBind();
	ib.UnBind();

	std::string filepath = "./basic.shader";
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)r_Width / (float)r_Height, 0.1f, 100.0f);
	glm::mat4 projection = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f);

	Shader shader(filepath);
	//shader.SetUniform("u_Color", 1.0f, 0.3f, 0.8f, 1.0f);

	Texture texture("./sadpepe.png", "texture_diffuse");
	texture.Bind();
	shader.SetUniform("textureIn", 0);
	shader.SetUniform("projection", projection);
	*/
	

	
	std::string filepath = "./3DShader.shader";

	Shader shader(filepath);

	Object3D obj("./resources/Survival_BackPack_2.fbx", "./resources/1001_albedo.jpg", "./resources/1001_metallic.jpg", "./resources/1001_normal.jpg", "./resources/1001_roughness.jpg", false);

	//glm::mat4 projection = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f);

	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)r_Width / (float)r_Height, 0.1f, 100.0f);
	glm::mat4 view = glm::mat4(1.0f);
	shader.SetUniform("projection", projection);
	shader.SetUniform("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	shader.SetUniform("model", model);
	

	while (!glfwWindowShouldClose(r_Window)) {
		glfwPollEvents();
		glClearColor(r_ClearColor.r, r_ClearColor.g, r_ClearColor.b, r_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//shader.Bind();
		//va.Bind();
		//ib.Bind();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
		obj.Draw(shader);


		glfwSwapBuffers(r_Window);
		glfwGetWindowSize(r_Window, &r_Width, &r_Height);
	}

	std::string fileContent = "WindowWidth : " + std::to_string(r_Width) + "\n" + "WindowHeight : " + std::to_string(r_Height) + "\n" + "VirtualRenderWidth : " + std::to_string(r_VirtualWidth) + "\n" + "VirtualRenderHeight : " + std::to_string(r_VirtualHeight) + "\n";
	WriteFile("Config.Saturn", fileContent);
	LOG_PASS("Latest file config saved!");
	LOG_PASS("DEBUG Content:\n" + fileContent);
}
