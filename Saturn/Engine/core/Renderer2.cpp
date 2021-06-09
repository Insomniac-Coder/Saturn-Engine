#include "Renderer2.h"
#include "DrawCall.h"

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

	int textureUnits;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
	LOG_INFO("This GPU supports " + std::to_string(textureUnits) + " texture slots at max");

	Saturn::DrawCall::SetMaxTextureSlots((unsigned short)textureUnits);
}

Saturn::Renderer::~Renderer()
{
}

void Saturn::Renderer::Run()
{
	Texture tex("./Textures/white.png");

	DrawCall dCall;

	Saturn::UI::UIElement ue(r_Window);

	RenderDataLoader rd("./RenderData/object.data");

	RenderData* data = rd.GetRenderData();

	r_ObjectVao = dCall.GetVertexArray();

	dCall.PushObject(data->Vertices, data->Indices, glm::vec3(0.0f), "", "", "", "");

	Camera cam(Saturn::CameraType::PERSPECTIVE);

	glm::vec3 lightPos(1.2f, 1.5f, -4.5f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, -5.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

	glm::mat4 projection;

	Shader shader("./Shaders/3DShader.shader");

	glm::vec3 lColor = glm::vec3(0.7f, 0.7f, 0.7f);

	if (cam.GetCameraType() == Saturn::CameraType::PERSPECTIVE) {
		projection = glm::perspective(glm::radians(cam.GetFov()), float(r_Width) / float(r_Height), cam.GetzNear(), cam.GetzFar());
	}

	LOG_INFO("Index Count in renderer: " + std::to_string(dCall.GetIndicesCount()));
	LOG_INFO("Used Buffer Space: " + std::to_string(dCall.GetUsedBufferSize()));

	while (!glfwWindowShouldClose(r_Window)) {
		glfwPollEvents();
		glClearColor(r_ClearColor.r, r_ClearColor.g, r_ClearColor.b, r_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		tex.Bind();
		shader.Bind();
		shader.SetUniform("material.diffuse", 0);
		shader.SetUniform("material.specular", 0);
		shader.SetUniform("light.position", lightPos);
		shader.SetUniform("viewPos", cam.GetTransform().Position);
		shader.SetUniform("material.shininess", 64.0f);
		shader.SetUniform("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		shader.SetUniform("light.diffuse", lColor);
		shader.SetUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.SetUniform("projection", projection);
		shader.SetUniform("view", cam.GetLookAt());
		shader.SetUniform("model", model);
		dCall.GetVertexArray()->Bind();
		glDrawElements(GL_TRIANGLES, dCall.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
		dCall.GetVertexArray()->UnBind();

		glfwSwapBuffers(r_Window);
		glfwGetWindowSize(r_Window, &r_Width, &r_Height);
	}

	std::string fileContent = "WindowWidth : " + std::to_string(r_Width) + "\n" + "WindowHeight : " + std::to_string(r_Height) + "\n" + "VirtualRenderWidth : " + std::to_string(r_VirtualWidth) + "\n" + "VirtualRenderHeight : " + std::to_string(r_VirtualHeight) + "\n";
	WriteFile("Config.Saturn", fileContent);
	LOG_PASS("Latest file config saved!");
	LOG_PASS("DEBUG Content:\n" + fileContent);
}