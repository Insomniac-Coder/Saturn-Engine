#include "UIElement.h"

Saturn::UI::UIElement::UIElement(GLFWwindow* windowRef) : u_Window(windowRef)
{
	const char* glsl_version = "#version 460";

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(u_Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();
}

void Saturn::UI::UIElement::DrawUI(glm::vec4& skyboxColor, float& x, float& y, float& z) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Text("Editor");
	ImGui::ColorEdit3("SkyBox Color", glm::value_ptr(skyboxColor));
	ImGui::SliderFloat("X-Rotation", &x, 0.0f, 360.0f);
	ImGui::SliderFloat("Y-Rotation", &y, 0.0f, 360.0f);
	ImGui::SliderFloat("Z-Rotation", &z, 0.0f, 360.0f);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Saturn::UI::UIElement::~UIElement()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
