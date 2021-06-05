#include "Renderer.h"
#include "FileIO.h"
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
	LOG_INFO((char*)glGetString(GL_VERSION));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	r_Vao = new VertexArray();
	r_Vao->Bind();
}

Saturn::Renderer::~Renderer()
{
}

void Saturn::Renderer::Run()
{

	//ModelLoader myModel("./3DObjects/monkey.fbx");

	RenderDataLoader rd("./RenderData/monkey.data");

	RenderData* data = rd.GetRenderData();

	r_Vbo = new VertexBuffer(data->Vertices);
	r_Ibo = new IndexBuffer(&(data->Indices)[0], data->Indices.size());

	r_Vao->AddAttribute(sizeof(((Vertex*)0)->Position) / sizeof(float));
	r_Vao->AddAttribute(sizeof(((Vertex*)0)->Normal) / sizeof(float));
	r_Vao->AddAttribute(sizeof(((Vertex*)0)->TexCoords) / sizeof(float));

	r_Vao->UnBind();
	r_Vbo->UnBind();
	r_Ibo->UnBind();

	Texture tex("./Textures/rock.jpg");
	Shader shader("./Shaders/3DShader.shader");
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)r_Width / (float)r_Height, 0.0f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), float(r_Width) / float(r_Height), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f)); // translate it down so it's at the center of the scene
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	
	LOG_INFO(std::to_string(glGetError()));

	while (!glfwWindowShouldClose(r_Window)) {
		glfwPollEvents();
		glClearColor(r_ClearColor.r, r_ClearColor.g, r_ClearColor.b, r_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tex.Bind();
		shader.Bind();
		shader.SetUniform("textureIn", 0);
		shader.SetUniform("projection", projection);
		shader.SetUniform("view", view);
		shader.SetUniform("model", model);
		r_Vao->Bind();
		glDrawElements(GL_TRIANGLES, data->Indices.size(), GL_UNSIGNED_INT, nullptr);
		r_Vao->UnBind();
		shader.UnBind();
		tex.UnBind();
		
		glfwSwapBuffers(r_Window);
		glfwGetWindowSize(r_Window, &r_Width, &r_Height);
	}

	std::string fileContent = "WindowWidth : " + std::to_string(r_Width) + "\n" + "WindowHeight : " + std::to_string(r_Height) + "\n" + "VirtualRenderWidth : " + std::to_string(r_VirtualWidth) + "\n" + "VirtualRenderHeight : " + std::to_string(r_VirtualHeight) + "\n";
	WriteFile("Config.Saturn", fileContent);
	LOG_PASS("Latest file config saved!");
	LOG_PASS("DEBUG Content:\n" + fileContent);
}
