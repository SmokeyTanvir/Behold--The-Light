#pragma once

#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

class GUI {
public:
    GUI();
    ~GUI();

    void Initialize(GLFWwindow* window);
    void Render();

private:
    void CreateGUIFrame();
    void CreateGameObjectProperties();

    GLFWwindow* window;
    bool show_demo_window;

    // Add other GUI-related variables and functions as needed.
};
