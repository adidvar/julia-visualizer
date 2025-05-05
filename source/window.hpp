#pragma once

#include <memory>

#include <glad/gl.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <wrappers/renderlist.hpp>
#include <wrappers/shader.hpp>

class Window
{
public:
  Window();
  ~Window();

  int loop();

  void interface();
  void background();

private:
  GLFWwindow* window_ = nullptr;

  std::unique_ptr<ShaderProgram> shader_program_ = nullptr;
  std::unique_ptr<RenderList> render_list_ = nullptr;
};
