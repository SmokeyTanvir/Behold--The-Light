#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>	
#include "drawing.h"
#include "ui.h"

int window_width = 900;
int window_height = 500;
float deltaTime;
float lastFrame;

// function prototypes
void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "halo", NULL, NULL);

	// check if the window has been created
	if (!window) {
		std::cout << "FAILED TO CREATE WINDOW\n";
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, framebuffer_resize_callback);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "FAILED TO INITIALIZE GLAD\n";
		return -1;
	}
	glEnable(GL_DEPTH_TEST);

	// Initialize ImGUI
	InitializeImGUI(window);

	float colorBuffer[3] = { 1.0f, 1.0f, 1.0f };

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(colorBuffer[0], colorBuffer[1], colorBuffer[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// setup deltaTime
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// start imgui frame
		startImGUIframe();

		ImGui::Begin("clear color");
		ImGui::ColorEdit3("color", colorBuffer);
		ImGui::End();

		// render UI
		renderImGUI();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	return 0;
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	window_width = width;
	window_height = height;
}