#include <memory>

#include "application.hpp"

#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x2.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
}

Application::~Application() {}

int Application::run()
{
  while (glfwWindowShouldClose(window_) == 0) {
    // imgui update
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    renderGUI();
    ImGui::Render();

    // clear
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // render
    renderBackground();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // swap
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }

  return 0;
}

void Application::renderGUI()
{
  ImGuiIO& imgui_io = ImGui::GetIO();
  {
    ImGui::Begin("Menu");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / imgui_io.Framerate,
                imgui_io.Framerate);

    ImGui::SliderFloat("Fractal X", &start_point_x_, -1.0F, 1.0F);
    ImGui::SliderFloat("Fractal Y", &start_point_y_, -1.0F, 1.0F);

    ImGui::SliderFloat("Window X", &window_start_x_, -1.0F, 1.0F);
    ImGui::SliderFloat("Window Y", &window_start_y_, -1.0F, 1.0F);
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

void Application::renderBackground()
{
  shader_program_->activate();

  auto transform = glm::mat4(1.0F);
  transform =
      glm::translate(transform, glm::vec3(window_start_x_, window_start_y_, 0));
  transform = glm::scale(
      transform, glm::vec3(window_scale_, window_scale_, window_scale_));

  glUniformMatrix4fv(
      uniform_transform_matrix_, 1, 0, glm::value_ptr(transform));
  glUniform2f(uniform_start_point_, start_point_x_, start_point_y_);

  render_list_->render();

  shader_program_->deactivate();
}
