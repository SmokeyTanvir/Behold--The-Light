#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>	
#include <utility/Camera.h>
#include <utility/framebuffer.h>
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

	// Initialize Camera
	Camera sceneCamera(glm::vec3(0.0f, 0.0f, 0.0f));
	// Camera variables
	float lastX = window_width / 2;
	float lastY = window_height / 2;

	// Create Transformation Matrices
	glm::mat4 view;
	glm::mat4 projection;

	// Initialize Scene Buffer
	FrameBuffer sceneBuffer = FrameBuffer(window_width, window_height);

	// Initialize ImGUI
	InitializeImGUI(window);

	// Load Models, shaders
	// models
	Model nanosuit("resources/models/floor/floor.obj");

	// shaders
	Shader modelShader("resources/shaders/default.vert", "resources/shaders/default.frag");

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// setup deltaTime
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// process Inputs
		sceneCamera.processKeyInputs(window, deltaTime);
		sceneCamera.ProcessMouseMovement(window, lastX, lastY);

		// Setup transformation matrices
		view = sceneCamera.GetViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), (float)window_width / window_height, 0.1f, 100.0f);

		// draw models/skybox etc
		glm::mat4 nanosuitModel(1.0f);
		drawModel(nanosuit, modelShader, nanosuitModel, view, projection);

		// start imgui frame
		startImGUIframe();

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