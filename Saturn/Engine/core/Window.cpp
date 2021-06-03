#include "Window.h"
#include <iostream>

Saturn::Window::Window(unsigned int& windowWidth, unsigned int& windowHeight, unsigned int& virtualWidth, unsigned int& virtualHeight) : w_Width(windowWidth), w_Height(windowHeight), w_VirtualWidth(virtualWidth), w_VirtualHeight(virtualHeight), w_Window(nullptr)
{

	if (!glfwInit()) {
		LOG_FAIL("GLFW Initialization failed!");
	}
	else
	{
		w_Window = glfwCreateWindow(w_Width, w_Height, "Saturn Engine", NULL, NULL);

		if (w_Window == nullptr) {
			LOG_FAIL("Window creation failed!");
			glfwTerminate();
		}
	}

	LOG_PASS("Window Created, Dimensions are " + std::to_string(windowWidth) + " x " + std::to_string(windowHeight));

	w_Renderer = new Saturn::Renderer(w_Width, w_Height, w_VirtualWidth, w_VirtualHeight, SendWindowRef());
}

Saturn::Window::~Window()
{
	if (w_Window != nullptr) {
		glfwDestroyWindow(w_Window);
	}
	glfwTerminate();
}


void Saturn::Window::Run() {
	w_Renderer->Run();
}