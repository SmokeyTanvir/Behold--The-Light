#include "Engine.h"

Engine::Engine(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height), windowTitle(title), window(nullptr) {
    Initialize();
    lastFrame = 0.0f;
    shader = Shader("shaders/model.vert", "shaders/model.frag");
    camera = Camera(glm::vec3(0.0f, 10.0f, 0.0f));
}

Engine::~Engine() {
    // Cleanup resources here
    glfwTerminate();
}

void Engine::Initialize() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n" << std::endl;
        return;
    }

    // glfwWindowHint(GLFW_SAMPLES, 8);
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n" << std::endl;
        glfwTerminate();
        // Handle the error accordingly
        return;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        // Handle the error accordingly
        return;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // glEnable(GL_MULTISAMPLE);

    // Load shaders, create camera, set up scene, etc.
    // ...
    Model scene("models/floor/scene.obj");
    gameObjects.push_back(scene);

    // Initialize GUI
    gui.Initialize(window);
}

void Engine::Run() {
    while (!glfwWindowShouldClose(window)) {
        ProcessInput();
        Update();
        Render();
    }
    // Cleanup and exit
}

void Engine::ProcessInput() {
    // Handle user input here
    // ...
    glfwPollEvents();

    if(!ImGui::GetIO().WantCaptureMouse)
        camera.ProcessMouseMovement(window);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void Engine::Update() {
    // Update game logic, camera, objects, etc.
    // ...
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Engine::Render() {
    // Clear the framebuffer, use shaders, render objects, render GUI, swap buffers
    // ...
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 1000.0f);

    // Render Objects
    shader.use();
    glm::mat4 sceneModel(1.0f);
    shader.setMVP(sceneModel, camera.GetViewMatrix(), projection);
    gameObjects[0].Draw(shader);

    // Render GUI
    gui.Render();

    // Swap the buffers in the end
    glfwSwapBuffers(window);
}
