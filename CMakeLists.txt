cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    julia-visualizer
    VERSION 0.2.0
    DESCRIPTION "This is a C++ project that renders Julia Set using OpenGL shaders"
    HOMEPAGE_URL "https://github.com/adidvar/julia-visualizer"
    LANGUAGES CXX C
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)


# ---- Declare library ----

add_library(
    julia-visualizer_lib

    source/wrappers/shader.cpp
    source/wrappers/renderlist.cpp
    source/window.cpp
    source/application.cpp
)


target_include_directories(
    julia-visualizer_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(julia-visualizer_lib PUBLIC cxx_std_17)

# ---- Dependency ----

find_package(opengl_system REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

include(cmake/glad.cmake)
include(cmake/imgui.cmake)

target_link_libraries(julia-visualizer_lib
    glfw opengl::opengl glm::glm glad imgui::imgui
)

# ---- Declare executable ----

add_executable(julia-visualizer_exe source/main.cpp)
add_executable(julia-visualizer::exe ALIAS julia-visualizer_exe)

set_property(TARGET julia-visualizer_exe PROPERTY OUTPUT_NAME julia-visualizer)

target_compile_features(julia-visualizer_exe PRIVATE cxx_std_17)

target_link_libraries(julia-visualizer_exe PRIVATE julia-visualizer_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT julia-visualizer_DEVELOPER_MODE)
    return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
    message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of julia-visualizer"
  )
endif()

include(cmake/dev-mode.cmake)
