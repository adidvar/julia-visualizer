#pragma once

#include <string>
#include <utility>

#include <glad/gl.h>

class ShaderProgram
{
  static const char* k_vertex_shader_text_;
  static const char* k_fragment_shader_text_;

public:
  ShaderProgram()
  {
    char error_log[512];
    int compile_status;

    // Compile vertex shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &k_vertex_shader_text_, nullptr);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);

    if (!compile_status) {
      glGetShaderInfoLog(vertex_shader, 512, nullptr, error_log);
      appendError("\nERROR::SHADER::VERTEX::COMPILATION::FAILED\n");
      appendError(error_log);
    }

    // Compile fragment shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &k_fragment_shader_text_, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);

    if (!compile_status) {
      glGetShaderInfoLog(fragment_shader, 512, nullptr, error_log);
      appendError("\nERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n");
      appendError(error_log);
    }

    // Skip link if compile failer
    if (!valid()) {
      appendError("\nERROR::SHADER::LINK::SKIPPED\n");
      return;
    }

    // Link shader program
    program_ = glCreateProgram();
    glAttachShader(program_, vertex_shader);
    glAttachShader(program_, fragment_shader);
    glLinkProgram(program_);
    glGetProgramiv(program_, GL_LINK_STATUS, &compile_status);

    if (!compile_status) {
      glGetProgramInfoLog(program_, 512, nullptr, error_log);
      appendError("\nERROR::SHADER::LINK::ERROR\n");
      appendError(error_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
  }

  ~ShaderProgram() { glDeleteProgram(program_); }

  ShaderProgram(const ShaderProgram&) = delete;
  auto operator=(const ShaderProgram&) -> ShaderProgram& = delete;

  ShaderProgram(ShaderProgram&& other) noexcept
  {
    std::swap(program_, other.program_);
    std::swap(error_, other.error_);
  }

  auto operator=(ShaderProgram&& other) noexcept -> ShaderProgram&
  {
    std::swap(program_, other.program_);
    std::swap(error_, other.error_);

    return *this;
  }

  void appendError(const std::string& part) { error_ += part; }

  bool valid() const { return error_.empty(); }

  void activate() const { glUseProgram(program_); }

  std::string getError() { return error_; }

  GLuint getUid() const { return program_; }

private:
  GLuint program_ = 0;
  std::string error_;
};
