#include <cstdlib>
#include <iostream>

#include "window.hpp"

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "imgui.h"

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

  auto* context = Window::getHandle(glfwGetWindowUserPointer(window));

  if (context->isMouseCaptureEnabled()) {
    context->handleMousePosition(cursor_x, cursor_y);
  }
}

void glfwHandleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
  ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

  auto* context = Window::getHandle(glfwGetWindowUserPointer(window));

  if (context->isMouseCaptureEnabled()) {
    context->handleMouseButton(button, action, mods);
  }
}

void glfwHandleMouseWheel(GLFWwindow* window, double x_offset, double y_offset)
{
  ImGui_ImplGlfw_ScrollCallback(window, x_offset, y_offset);

  auto* context = Window::getHandle(glfwGetWindowUserPointer(window));

  if (context->isMouseCaptureEnabled()) {
    context->handleMouseWheel(x_offset, y_offset);
  }
}

void glfwHandleKeyboardKey(
    GLFWwindow* window, int key, int scancode, int action, int mods)
{
  ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);

  auto* context = Window::getHandle(glfwGetWindowUserPointer(window));

  if (context->isKeyboardCaptureEnabled()) {
    context->handleKeyboardKey(key, scancode, action, mods);
  }
}

void glfwHandleFrameBufferResize(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);

  Window::getHandle(glfwGetWindowUserPointer(window))
      ->updateWindowRatio(width, height);
}

}  // namespace

Window* Window::getHandle(void* p)
{
  return static_cast<Window*>(p);
}

void Window::updateWindowRatio(int width, int height)
{
  window_ratio_ = static_cast<float>(width) / static_cast<float>(height);
  window_width_ = width;
  window_height_ = height;
}

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
  window_ = glfwCreateWindow(
      window_width_, window_height_, "Julia", nullptr, nullptr);
  if (window_ == nullptr) {
    std::cerr << "glfw window init error";
    exit(-1);
  }
  updateWindowRatio(window_width_, window_height_);

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

  // write a window pointer
  glfwSetWindowUserPointer(window_, this);

  // override callbacks I need
  glfwSetCursorPosCallback(window_, glfwHandleMousePosition);
  glfwSetMouseButtonCallback(window_, glfwHandleMouseButton);
  glfwSetScrollCallback(window_, glfwHandleMouseWheel);
  glfwSetKeyCallback(window_, glfwHandleKeyboardKey);
  glfwSetFramebufferSizeCallback(window_, glfwHandleFrameBufferResize);
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

int Window::run()
{
  while (glfwWindowShouldClose(window_) == 0) {
    // imgui update
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // clear
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    render();

    // render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // swap
    glfwSwapBuffers(window_);
    glfwPollEvents();

    const ImGuiIO& imgui_io = ImGui::GetIO();

    enableCaptureMouse(!imgui_io.WantCaptureMouse);
    enableCaptureKeyboard(!imgui_io.WantCaptureKeyboard);
  }

  return 0;
}
