#include <memory>

#include "application.hpp"

#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x2.hpp>

#include "glad/gl.h"
#include "imgui.h"
#include "wrappers/renderlist.hpp"
#include "wrappers/shader.hpp"

Application::Application()
    : render_list_(std::make_unique<RenderList>())
    , shader_program_(std::make_unique<ShaderProgram>())
{
  uniform_start_point_ =
      glGetUniformLocation(shader_program_->getUid(), "uniform_start_point");
  uniform_transform_matrix_ = glGetUniformLocation(shader_program_->getUid(),
                                                   "uniform_transform_matrix");

  shader_program_->activate();
}

Application::~Application() = default;

void Application::render()
{
  renderGUI();
  renderBackground();
}

void Application::renderGUI()
{
  {
    const ImGuiIO& imgui_io = ImGui::GetIO();
    ImGui::Begin("Menu");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0F / imgui_io.Framerate,
                imgui_io.Framerate);

    ImGui::SliderFloat2("Fractal", &start_point_x_, -0.3F, 0.3F);

    ImGui::SliderFloat2("Window", &window_start_x_, -1.0F, 1.0F);

    ImGui::SliderFloat("Window Scale", &window_scale_, 0, 10.0F);

    ImGui::End();

    // Print shader compilation errors
    if (!shader_program_->valid()) {
      ImGui::Begin("Shader compilation error");
      ImGui::Text("%s", shader_program_->getError().c_str());
      ImGui::End();
    }
  }
}

void Application::renderBackground() const
{
  auto transform = glm::mat4(1.0F);

  float ratio = sqrtf(window_ratio_);

  transform = glm::scale(transform, glm::vec3(ratio, 1.0 / ratio, 1));

  transform = glm::translate(
      transform, glm::vec3(2 * window_start_x_, -2 * window_start_y_, 0));

  transform = glm::scale(transform, glm::vec3(window_scale_, window_scale_, 1));

  glUniformMatrix4fv(
      uniform_transform_matrix_, 1, 0, glm::value_ptr(transform));
  glUniform2f(uniform_start_point_, start_point_x_, start_point_y_);

  render_list_->render();
}

void Application::handleMousePosition(double cursor_x, double cursor_y)
{
  if (movement_mode_) {
    window_start_x_ += (cursor_x_ - cursor_x) / window_width_ * window_scale_;
    window_start_y_ += (cursor_y_ - cursor_y) / window_height_ * window_scale_;

    cursor_x_ = cursor_x;
    cursor_y_ = cursor_y;
  }
}

void Application::handleMouseButton(int button, int action, int /*mods*/)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) {
    movement_mode_ = (action == GLFW_PRESS);
    glfwGetCursorPos(window_, &cursor_x_, &cursor_y_);
  }
}

constexpr float kMouseWheelSensitivity = 1.1F;

void Application::handleMouseWheel(double /*wheel_x*/, double wheel_y)
{
  const float scale_factor =
      (wheel_y < 0) ? kMouseWheelSensitivity : 1.0F / kMouseWheelSensitivity;
  window_scale_ *= scale_factor;
}

void Application::handleKeyboardKey(int key, int scancode, int action, int mods)
{
}
