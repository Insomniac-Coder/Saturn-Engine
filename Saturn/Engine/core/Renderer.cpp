#include "Renderer.h"
#include "FileIO.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "../Editor/UIElement.h"

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
	Saturn::UI::UIElement ue(r_Window);

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

	Texture tex("./Textures/crate.png");
	Texture tex2(".Textures/crate_specular.png");
	Shader shader("./Shaders/3DShader.shader");
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)r_Width / (float)r_Height, 0.0f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), float(r_Width) / float(r_Height), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f);
	glm::mat4 view = glm::mat4(1.0f);

	glm::vec3 lightPos(1.2f, 1.5f, -4.5f); //light position
	
	LOG_INFO(std::to_string(glGetError()));
	float xRot = 0.0f;
	float yRot = 0.0f;
	float zRot = 0.0f;

	while (!glfwWindowShouldClose(r_Window)) {
		glfwPollEvents();
		glClearColor(r_ClearColor.r, r_ClearColor.g, r_ClearColor.b, r_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(zRot), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

		tex.Bind();
		tex2.Bind(1);
		shader.Bind();
		shader.SetUniform("material.diffuse", 0);
		shader.SetUniform("material.specular", 1);
		shader.SetUniform("light.position", lightPos);
		shader.SetUniform("viewPos", glm::vec3(0.0f));
		shader.SetUniform("material.shininess", 64.0f);
		shader.SetUniform("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		shader.SetUniform("light.diffuse", glm::vec3(0.7f, 0.7f, 0.7f));
		shader.SetUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.SetUniform("projection", projection);
		shader.SetUniform("view", view);
		shader.SetUniform("model", model);
		r_Vao->Bind();
		glDrawElements(GL_TRIANGLES, data->Indices.size(), GL_UNSIGNED_INT, nullptr);
		r_Vao->UnBind();
		shader.UnBind();
		tex.UnBind();

		ue.DrawUI(r_ClearColor, xRot, yRot, zRot);
		
		glfwSwapBuffers(r_Window);
		glfwGetWindowSize(r_Window, &r_Width, &r_Height);
	}

	std::string fileContent = "WindowWidth : " + std::to_string(r_Width) + "\n" + "WindowHeight : " + std::to_string(r_Height) + "\n" + "VirtualRenderWidth : " + std::to_string(r_VirtualWidth) + "\n" + "VirtualRenderHeight : " + std::to_string(r_VirtualHeight) + "\n";
	WriteFile("Config.Saturn", fileContent);
	LOG_PASS("Latest file config saved!");
	LOG_PASS("DEBUG Content:\n" + fileContent);
}
