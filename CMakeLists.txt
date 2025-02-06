cmake_minimum_required(VERSION 3.30)
project(JuliaSet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)

add_executable(JuliaSet src/main.cpp src/shader.h src/shader.cpp)
target_link_libraries(JuliaSet opengl::opengl glfw glad::glad glm::glm)

install(TARGETS JuliaSet
    RUNTIME DESTINATION .
)

install(FILES shaders/FragmentShader.txt shaders/VertexShader.txt DESTINATION .)
