#include "UIElement.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Saturn::UI::UIElement::UIElement(GLFWwindow* windowRef) : u_Window(windowRef)
{
	const char* glsl_version = "#version 460";

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(u_Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();
}

void Saturn::UI::UIElement::DrawUI(glm::vec4& skyboxColor) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "Ctrl + N"))
			{
				//Do something
			}
			if (ImGui::MenuItem("Close", "Alt + F4"))
			{
				glfwSetWindowShouldClose(u_Window, GLFW_TRUE);
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	ImGui::Text("Editor");
	ImGui::ColorEdit3("SkyBox Color", glm::value_ptr(skyboxColor));
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Saturn::UI::UIElement::~UIElement()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
