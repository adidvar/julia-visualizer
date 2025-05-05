#include <cstdlib>
#include <iostream>

#include "window.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "imgui.h"

constexpr unsigned kWindowWidth = 1280;
constexpr unsigned kWindowHeight = 720;

static void errorEvent(int error, const char* description)
{
  std::cerr << "glfw error: " << description;
}

Window::Window()
{
  // GLFW Init
  if (glfwInit() == 0) {
    std::cerr << "glfw init error";
    exit(-1);
  }
  glfwSetErrorCallback(errorEvent);

  // OPENGL context settings1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // WINDOW init
  window_ =
      glfwCreateWindow(kWindowWidth, kWindowHeight, "Julia", nullptr, nullptr);
  if (window_ == nullptr) {
    std::cerr << "glfw window init error";
    exit(-1);
  }

  glfwSetWindowUserPointer(window_, this);
  glfwMakeContextCurrent(window_);

  // load GLAD
  gladLoadGL(glfwGetProcAddress);

  // enable VSYNC
  glfwSwapInterval(1);

  // init imgui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window_, /*install_callbacks=*/true);
  ImGui_ImplOpenGL3_Init("#version 150");
}

Window::~Window()
{
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window_);
  glfwTerminate();
}
