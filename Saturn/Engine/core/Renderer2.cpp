#include "Renderer2.h"

static void WindowResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Saturn::Renderer::Renderer(unsigned int windowWidth, unsigned int windowHeight, unsigned int virtualWidth, unsigned int virtualHeight, GLFWwindow* windowRef) : r_Width(windowWidth), r_Height(windowHeight), r_VirtualWidth(virtualWidth), r_VirtualHeight(virtualHeight), r_Window(windowRef)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(r_Window);
	glfwSetWindowSizeCallback(r_Window, WindowResize);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	LOG_INFO((char*)glGetString(GL_VERSION));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glfwSwapInterval(0);
	glfwWindowHint(GLFW_SAMPLES, 8);
	glEnable(GL_MULTISAMPLE);

	int textureUnits;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
	LOG_INFO("This GPU supports " + std::to_string(textureUnits) + " texture slots at max");

	Saturn::DrawCall::SetMaxTextureSlots((unsigned short)textureUnits);

	defaultTexture = new Texture("./Textures/white.png");
}

Saturn::Renderer::~Renderer()
{
}

void Saturn::Renderer::Run()
{
	Texture tex("./Textures/white.png");
	Texture tex2("./Textures/red.png");

	DrawCall dCall;
	DrawCall dCall2;
	DrawCall dCall3;
	int modelNum = 27;

	Saturn::UI::UIElement ue(r_Window);

	RenderDataLoader rd("./RenderData/object.data");
	RenderData* data = rd.GetRenderData();

	for (int i = 0; i < modelNum; i++) {
		dCall.PushObject(data->Vertices, data->Indices, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "", "", "", "");
		dCall2.PushObject(data->Vertices, data->Indices, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "", "", "", "");
		dCall3.PushObject(data->Vertices, data->Indices, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "", "", "", "");
	}

	Camera cam(Saturn::CameraType::PERSPECTIVE);

	glm::vec3 lightPos(1.2f, 1.5f, -4.5f);

	std::vector<glm::mat4> modelList;
	std::vector<glm::mat4> modelList2;
	std::vector<glm::mat4> modelList3;

	for (int i = 0; i < modelNum; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(4.0f, -2.0f, -5.0f * (i + 1)));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		modelList.push_back(model);
	}

	for (int i = 0; i < modelNum; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.0f, -2.0f, -5.0f * (i + 1)));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		modelList2.push_back(model);
	}

	for (int i = 0; i < modelNum; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -5.0f * (i + 1)));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		modelList3.push_back(model);
	}

	glm::mat4 projection;

	Shader shader("./Shaders/3DShader.shader");

	glm::vec3 lColor = glm::vec3(0.7f, 0.7f, 0.7f);

	if (cam.GetCameraType() == Saturn::CameraType::PERSPECTIVE) {
		projection = glm::perspective(glm::radians(cam.GetFov()), float(r_Width) / float(r_Height), cam.GetzNear(), cam.GetzFar());
	}

	LOG_INFO("Used Buffer Space for draw call 1(in Percentage): " + std::to_string(((float)dCall.GetUsedBufferSize() / (float)(500000 * sizeof(Saturn::Vertex))) * (float)100));
	LOG_INFO("Used Buffer Space for draw call 2 (in Percentage): " + std::to_string(((float)dCall2.GetUsedBufferSize() / (float)(500000 * sizeof(Saturn::Vertex))) * (float)100));

	while (!glfwWindowShouldClose(r_Window)) {
		glfwPollEvents();
		glClearColor(r_ClearColor.r, r_ClearColor.g, r_ClearColor.b, r_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tex.Bind();
		tex2.Bind(1);
		shader.Bind();
		shader.SetUniform("light.position", lightPos);
		shader.SetUniform("viewPos", cam.GetTransform().Position);
		shader.SetUniform("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		shader.SetUniform("light.diffuse", lColor);
		shader.SetUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.SetUniform("projection", projection);
		shader.SetUniform("view", cam.GetLookAt());
		for (int i = 0; i < modelNum; i++) {
			shader.SetUniform("model[" + std::to_string(i) + "]", modelList[i]);

			shader.SetUniform("diffuse[" + std::to_string(i) + "]",  0);
			shader.SetUniform("specular[" + std::to_string(i) + "]", 0);
			shader.SetUniform("shininess[" + std::to_string(i) + "]",  128.0f);
		}
		dCall.GetVertexArray()->Bind();
		glDrawElements(GL_TRIANGLES, dCall.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
		dCall.GetVertexArray()->UnBind();
		shader.UnBind();

		
		shader.Bind();
		shader.SetUniform("light.position", lightPos);
		shader.SetUniform("viewPos", cam.GetTransform().Position);
		shader.SetUniform("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		shader.SetUniform("light.diffuse", lColor);
		shader.SetUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.SetUniform("projection", projection);
		shader.SetUniform("view", cam.GetLookAt());
		for (int i = 0; i < modelNum; i++) {
			shader.SetUniform("model[" + std::to_string(i) + "]", modelList2[i]);

			shader.SetUniform("diffuse[" + std::to_string(i) + "]", 1);
			shader.SetUniform("specular[" + std::to_string(i) + "]", 0);
			shader.SetUniform("shininess[" + std::to_string(i) + "]", 64.0f);
		}
		dCall2.GetVertexArray()->Bind();
		glDrawElements(GL_TRIANGLES, dCall2.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
		dCall2.GetVertexArray()->UnBind();
		shader.UnBind();

		shader.Bind();
		shader.SetUniform("light.position", lightPos);
		shader.SetUniform("viewPos", cam.GetTransform().Position);
		shader.SetUniform("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		shader.SetUniform("light.diffuse", lColor);
		shader.SetUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.SetUniform("projection", projection);
		shader.SetUniform("view", cam.GetLookAt());
		for (int i = 0; i < modelNum; i++) {
			shader.SetUniform("model[" + std::to_string(i) + "]", modelList3[i]);

			shader.SetUniform("diffuse[" + std::to_string(i) + "]", 0);
			shader.SetUniform("specular[" + std::to_string(i) + "]", 0);
			shader.SetUniform("shininess[" + std::to_string(i) + "]", 32.0f);
		}
		dCall3.GetVertexArray()->Bind();
		glDrawElements(GL_TRIANGLES, dCall3.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
		dCall3.GetVertexArray()->UnBind();
		shader.UnBind();
		

		ue.DrawUI(r_ClearColor);

		glfwSwapBuffers(r_Window);
		glfwGetWindowSize(r_Window, &r_Width, &r_Height);
	}

	std::string fileContent = "WindowWidth : " + std::to_string(r_Width) + "\n" + "WindowHeight : " + std::to_string(r_Height) + "\n" + "VirtualRenderWidth : " + std::to_string(r_VirtualWidth) + "\n" + "VirtualRenderHeight : " + std::to_string(r_VirtualHeight) + "\n";
	WriteFile("Config.Saturn", fileContent);
	LOG_PASS("Latest file config saved!");
	LOG_PASS("DEBUG Content:\n" + fileContent);
}