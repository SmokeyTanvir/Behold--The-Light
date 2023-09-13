#include "GUI.h"
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h> // Include this for docking functions

GUI::GUI() : show_demo_window(false) {
    // Initialize other GUI-related variables here.
}

GUI::~GUI() {
    // Cleanup resources and ImGui context here.
}

void GUI::Initialize(GLFWwindow* window) {
    this->window = window;

    // Initialize ImGui context for GLFW and OpenGL3
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    // Enable docking and dragging windows out of the main window
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");


    // Load fonts, setup styles, and other ImGui initialization as needed.
    ImGui::StyleColorsClassic();
}

void GUI::Render() {
    // Start a new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create GUI elements and windows here
    CreateGUIFrame();

    // Render your custom GUI components
    // CreateGameObjectProperties();

    // Render ImGui frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and render additional windows (docking)
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void GUI::CreateGUIFrame() {
    ImGui::Begin("window");
    ImGui::Text("Framerate: %.2f fps", ImGui::GetIO().Framerate);
    ImGui::End();
}

void GUI::CreateGameObjectProperties() {
    // Create a window to display properties of a selected GameObject
    ImGui::Begin("GameObject Properties");

    // Add properties and controls for the selected object

    ImGui::End();
}
