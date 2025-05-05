#pragma once

#include <array>

#include "glad/gl.h"

class RenderList
{
  static std::array<float, 12> k_vertices_;
  static std::array<unsigned, 6> k_indices_;

public:
  RenderList()
  {
    glGenVertexArrays(1, &vertex_array_object_);
    glGenBuffers(1, &index_array_object_);
    glGenBuffers(1, &point_array_object_);

    // bind VAO
    glBindVertexArray(vertex_array_object_);

    glBindBuffer(GL_ARRAY_BUFFER, point_array_object_);
    glBufferData(GL_ARRAY_BUFFER,
                 k_vertices_.size() * sizeof(float),
                 k_vertices_.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_array_object_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 k_indices_.size() * sizeof(unsigned),
                 k_indices_.data(),
                 GL_STATIC_DRAW);

    // format of input values set up
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  ~RenderList()
  {
    glDeleteVertexArrays(1, &vertex_array_object_);
    glDeleteBuffers(1, &point_array_object_);
    glDeleteBuffers(1, &index_array_object_);
  }

  void render() const
  {
    glBindVertexArray(vertex_array_object_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
  }

private:
  GLuint vertex_array_object_ = 0;
  GLuint point_array_object_ = 0;
  GLuint index_array_object_ = 0;
};
