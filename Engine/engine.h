#pragma once

#include <glad/glad.h>
#include "GUI.h"
#include <vector>
#include <string>
#include <utility/Camera.h>
#include <utility/Shader.h>
#include <utility/Model.h>

class Engine {
public:
    Engine(int width, int height, const char* title);
    ~Engine();

    void Run();

private:
    void Initialize();
    void ProcessInput();
    void Update();
    void Render();

    float deltaTime;
    float lastFrame;

    int windowWidth;
    int windowHeight;
    const char* windowTitle;
    GLFWwindow* window;

    Camera camera;
    Shader shader;
    std::vector<Model> gameObjects;
    GUI gui;
};
