#include <cstdlib>
#include <iostream>

#include "window.hpp"

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "imgui.h"

constexpr unsigned kWindowWidth = 1280;
constexpr unsigned kWindowHeight = 720;

namespace
{

void glfwHandleError(int error, const char* description)
{
  std::cerr << "GLFW::ERROR::" << error << "\n" << description;
}

void glfwHandleMousePosition(GLFWwindow* window,
                             double cursor_x,
                             double cursor_y)
{
  ImGui_ImplGlfw_CursorPosCallback(window, cursor_x, cursor_y);
}

void glfwHandleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
  ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void glfwHandleMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{
  ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

void glfwHandleKeyboardKey(
    GLFWwindow* window, int key, int scancode, int action, int mods)
{
  ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

}  // namespace

Window::Window()
{
  // GLFW Init
  if (glfwInit() == 0) {
    std::cerr << "glfw init error";
    exit(-1);
  }
  glfwSetErrorCallback(glfwHandleError);

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

  // init imgui backend
  ImGui_ImplGlfw_InitForOpenGL(window_, /*install_callbacks=*/true);
  ImGui_ImplOpenGL3_Init("#version 150");

  // override callbacks I need
  glfwSetCursorPosCallback(window_, glfwHandleMousePosition);
  glfwSetMouseButtonCallback(window_, glfwHandleMouseButton);
  glfwSetScrollCallback(window_, glfwHandleMouseWheel);
  glfwSetKeyCallback(window_, glfwHandleKeyboardKey);
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
