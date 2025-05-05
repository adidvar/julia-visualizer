#include <cstdlib>
#include <iostream>
#include <memory>

#include "window.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "imgui.h"
#include "wrappers/renderlist.hpp"

constexpr unsigned kWindowWidth = 1280;
constexpr unsigned kWindowHeight = 720;

void errorEvent(int error, const char* description)
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

  gladLoadGL(glfwGetProcAddress);

  glfwSwapInterval(1);

  // context is fully initialized

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window_, /*install_callbacks=*/true);
  ImGui_ImplOpenGL3_Init("#version 150");

  // init shaders
  shader_program_ = std::make_unique<ShaderProgram>();

  // init VAO
  render_list_ = std::make_unique<RenderList>();
}

Window::~Window()
{
  glfwDestroyWindow(window_);
  glfwTerminate();
}

int Window::loop()
{
  while (glfwWindowShouldClose(window_) == 0) {
    glfwPollEvents();

    // frame preparation
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // generation ui
    interface();

    // render ui
    ImGui::Render();

    // scene clear
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // render background

    background();

    // render ui
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // swap
    glfwSwapBuffers(window_);
  }

  return 0;
}

void Window::interface()
{
  ImGuiIO& imgui_io = ImGui::GetIO();
  {
    ImGui::Begin("Menu");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / imgui_io.Framerate,
                imgui_io.Framerate);
    ImGui::End();

    // Print shader compilation errors
    if (!shader_program_->valid()) {
      ImGui::Begin("Shader compilation error");
      ImGui::Text("%s", shader_program_->getError().c_str());
      ImGui::End();
    }
  }
}

void Window::background()
{
  shader_program_->activate();

  render_list_->render();

  shader_program_->deactivate();
}
