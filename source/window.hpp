#pragma once

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

protected:
  GLFWwindow* window_ = nullptr;
};
