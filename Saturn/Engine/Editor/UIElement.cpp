#include "UIElement.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Saturn::UI::UIElement::UIElement(GLFWwindow* windowRef) : u_Window(windowRef)
{
	const char* glsl_version = "#version 460";

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(u_Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();
}

void Saturn::UI::UIElement::DrawUI(glm::vec4& skyboxColor, float& x, float& y, float& z, glm::vec3& lightColor, float& camXRot, float& camYRot, float& camZRot, float& camXPos, float& camYPos, float& camZPos) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New"))
			{
				//Do something
			}
			if (ImGui::MenuItem("Close"))
			{
				glfwSetWindowShouldClose(u_Window, GLFW_TRUE);
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}


	ImGui::Text("Editor");
	ImGui::ColorEdit3("SkyBox Color", glm::value_ptr(skyboxColor));
	ImGui::SliderFloat("X-Rotation", &x, 0.0f, 360.0f);
	ImGui::SliderFloat("Y-Rotation", &y, 0.0f, 360.0f);
	ImGui::SliderFloat("Z-Rotation", &z, 0.0f, 360.0f);
	ImGui::ColorEdit3("Light Color", glm::value_ptr(lightColor));
	ImGui::Text("Camera Rotation");
	ImGui::SliderFloat("Camera X-Rotation", &camXRot, 0.0f, 360.0f);
	ImGui::SliderFloat("Camera Y-Rotation", &camYRot, 0.0f, 360.0f);
	ImGui::SliderFloat("Camera X-Position", &camXPos, -10.0f, 10.0f);
	ImGui::SliderFloat("Camera Y-Position", &camYPos, -10.0f, 10.0f);
	ImGui::SliderFloat("Camera Z-Position", &camZPos, -10.0f, 10.0f);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Saturn::UI::UIElement::~UIElement()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
