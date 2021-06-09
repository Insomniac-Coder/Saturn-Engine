#include "Renderer.h"
#include "FileIO.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "../Editor/UIElement.h"
#include "Camera.h"

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

	ModelLoader myModel("./3DObjects/crysis.fbx");

	RenderDataLoader rd("./RenderData/object.data");

	RenderData* data = rd.GetRenderData();

	Camera cam(Saturn::CameraType::PERSPECTIVE);
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	float x, y, z, a, b, c;
	a = b = c = 0.0f;

	x = cam.GetTransform().Rotation.x;
	y = cam.GetTransform().Rotation.y;
	z = cam.GetTransform().Rotation.z;

	glm::vec3 rotation = cam.GetTransform().Rotation;

	r_Vbo = new VertexBuffer(data->Vertices.size());
	r_Ibo = new IndexBuffer(data->Indices.size());

	r_Vao->AddAttribute(sizeof(((Vertex*)0)->Position) / sizeof(float));
	r_Vao->AddAttribute(sizeof(((Vertex*)0)->Normal) / sizeof(float));
	r_Vao->AddAttribute(sizeof(((Vertex*)0)->TexCoords) / sizeof(float));

	r_Vao->UnBind();
	r_Vbo->UnBind();
	r_Ibo->UnBind();

	Texture tex("./Textures/white.png");
	Texture tex2(".Textures/white.png");
	Shader shader("./Shaders/3DShader.shader");
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)r_Width / (float)r_Height, 0.0f, 100.0f);
	glm::mat4 projection;

	if (cam.GetCameraType() == Saturn::CameraType::PERSPECTIVE) {
		projection = glm::perspective(glm::radians(cam.GetFov()), float(r_Width) / float(r_Height), cam.GetzNear(), cam.GetzFar());
	}

	//glm::mat4 projection = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f);
	glm::mat4 view = glm::mat4(1.0f);

	glm::vec3 lightPos(1.2f, 1.5f, -4.5f); //light position
	
	LOG_INFO(std::to_string(glGetError()));
	float xRot = 0.0f;
	float yRot = 0.0f;
	float zRot = 0.0f;
	glm::vec3 lColor = glm::vec3(0.7f, 0.7f, 0.7f);

	r_Vbo->AddDataToBuffer(0, data->Vertices);
	r_Ibo->AddDataToBuffer(0, data->Indices);

	while (!glfwWindowShouldClose(r_Window)) {
		glfwPollEvents();
		glClearColor(r_ClearColor.r, r_ClearColor.g, r_ClearColor.b, r_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -5.0f)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(zRot), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

		cam.SetPosition(glm::vec3(a, b, c));
		cam.SetRotation(glm::vec3(x, y, z));

		tex.Bind();
		tex2.Bind(1);
		shader.Bind();
		shader.SetUniform("material.diffuse", 0);
		shader.SetUniform("material.specular", 1);
		shader.SetUniform("light.position", lightPos);
		shader.SetUniform("viewPos", cam.GetTransform().Position);
		shader.SetUniform("material.shininess", 64.0f);
		shader.SetUniform("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		shader.SetUniform("light.diffuse", lColor);
		shader.SetUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.SetUniform("projection", projection);
		shader.SetUniform("view", cam.GetLookAt());
		shader.SetUniform("model", model);
		r_Vao->Bind();
		glDrawElements(GL_TRIANGLES, data->Indices.size(), GL_UNSIGNED_INT, nullptr);
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f));
		shader.SetUniform("model", model);
		glDrawElements(GL_TRIANGLES, data->Indices.size(), GL_UNSIGNED_INT, nullptr);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0f));
		shader.SetUniform("model", model);
		glDrawElements(GL_TRIANGLES, data->Indices.size(), GL_UNSIGNED_INT, nullptr);
		r_Vao->UnBind();
		shader.UnBind();
		tex.UnBind();
		tex2.UnBind();

		ue.DrawUI(r_ClearColor, xRot, yRot, zRot, lColor, x, y, z, a, b, c);
		
		glfwSwapBuffers(r_Window);
		glfwGetWindowSize(r_Window, &r_Width, &r_Height);
	}

	std::string fileContent = "WindowWidth : " + std::to_string(r_Width) + "\n" + "WindowHeight : " + std::to_string(r_Height) + "\n" + "VirtualRenderWidth : " + std::to_string(r_VirtualWidth) + "\n" + "VirtualRenderHeight : " + std::to_string(r_VirtualHeight) + "\n";
	WriteFile("Config.Saturn", fileContent);
	LOG_PASS("Latest file config saved!");
	LOG_PASS("DEBUG Content:\n" + fileContent);
}
