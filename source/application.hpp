#pragma once

#include <memory>

#include "window.hpp"
#include "wrappers/renderlist.hpp"
#include "wrappers/shader.hpp"

class Application : public Window
{
public:
  Application();
  ~Application();

  int run();

  void renderGUI();
  void renderBackground();

  void processsInput();

  void handleMousePosition(double cursor_x, double cursor_y) override {}

  void handleMouseButton(int button, int action, int mods) override {}

  void handleMouseWheel(double wheel_x, double wheel_y) override {}

  void handleKeyboardKey(int key, int scancode, int action, int mods) override
  {
  }

private:
  std::unique_ptr<RenderList> render_list_ = nullptr;
  std::unique_ptr<ShaderProgram> shader_program_ = nullptr;

  GLint uniform_start_point_ = 0;

  float start_point_x_ = 0;
  float start_point_y_ = 0;

  GLint uniform_transform_matrix_ = 0;

  float window_start_x_ = 0;
  float window_start_y_ = 0;
  float window_scale_ = 1;
};
