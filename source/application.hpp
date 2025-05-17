#pragma once

#include <memory>

#include <glad/gl.h>

#include <glm/vec3.hpp>

#include "window.hpp"
#include "wrappers/renderlist.hpp"
#include "wrappers/shader.hpp"

class Application final : public Window
{
public:
  Application();
  ~Application() override;

  void render() override;

  void renderGUI();
  void renderBackground() const;

  void handleMousePosition(double cursor_x, double cursor_y) override;
  void handleMouseButton(int button, int action, int mods) override;
  void handleMouseWheel(double wheel_x, double wheel_y) override;
  void handleKeyboardKey(int key, int scancode, int action, int mods) override;

private:
  std::unique_ptr<RenderList> render_list_ = nullptr;
  std::unique_ptr<ShaderProgram> shader_program_ = nullptr;

  GLint uniform_start_point_ = 0;

  float start_point_x_ = 0;
  float start_point_y_ = 0;

  GLint uniform_iterations_ = 0;

  int iterations_ = 50;

  GLint uniform_transform_matrix_ = 0;

  float window_start_x_ = 0;
  float window_start_y_ = 0;
  float window_scale_ = 1;

  GLint uniform_radius_ = 0;

  float radius_ = 100;

  GLint uniform_back_color_ = 0;

  glm::vec3 back_color_ = glm::vec3(0,0,0);

  GLint uniform_front_color_ = 0;

  glm::vec3 front_color_ = glm::vec3(0,0,0);

  bool movement_mode_ = false;

  double cursor_x_ = 0;
  double cursor_y_ = 0;
};
