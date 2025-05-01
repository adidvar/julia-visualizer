include(FetchContent)

FetchContent_Declare(
  imgui
  URL https://github.com/ocornut/imgui/archive/refs/heads/docking.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})

add_library(imgui STATIC
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp

  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set_target_properties(imgui PROPERTIES COMPILE_OPTIONS "")
set_target_properties(imgui PROPERTIES COMPILE_DEFINITIONS "")
set_target_properties(imgui PROPERTIES COMPILE_FLAGS "")

target_include_directories(imgui
PUBLIC
  ${IMGUI_DIR}
  ${IMGUI_DIR}/backends
)

find_package(glfw3 REQUIRED)
target_link_libraries(imgui glfw glad)

add_library(imgui::imgui ALIAS imgui)
