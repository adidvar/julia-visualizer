#include "window.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "glad/gl.h"

#include <cstdlib>
#include <iostream>

constexpr uint window_width = 1280;
constexpr uint window_height = 720;

Window::Window() {
   //GLFW Init
   if(glfwInit() == 0){
       std::cerr << "glfw init error";
       exit(-1);
   }
   glfwSetErrorCallback(&Window::errorEvent);

   // OPENGL context settings1
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   //WINDOW init
   m_window = glfwCreateWindow(window_width, window_height, "Julia", nullptr, nullptr);
   if (m_window == nullptr)
   {
       std::cerr << "glfw window init error";
       exit(-1);
   }
   glfwSetFramebufferSizeCallback(m_window, Window::framBufferSizeEvent);

   glfwSetWindowUserPointer(m_window, this);
   glfwMakeContextCurrent(m_window);

   gladLoadGL(glfwGetProcAddress);

   glfwSwapInterval(1);

   //context is fully initialized

   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO(); (void)io;
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

   ImGui::StyleColorsDark();

   ImGui_ImplGlfw_InitForOpenGL(m_window, true);
   ImGui_ImplOpenGL3_Init("#version 150");
}

void Window::errorEvent(int error, const char * description){
    std::cerr << "glfw error: " << description;
}

void Window::framBufferSizeEvent(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

Window::~Window(){
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

int Window::loop(){

    while (glfwWindowShouldClose(m_window) == 0)
    {
        glfwPollEvents();

        //frame preparation
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //generation ui
        interface();

        //render ui
        ImGui::Render();

        //scene clear
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);

        //render background

        //render ui
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //swap
        glfwSwapBuffers(m_window);
    }

    return 0;
}

void Window::interface(){
    ImGuiIO& imgui_io = ImGui::GetIO();
    {
        ImGui::Begin("Menu");

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / imgui_io.Framerate, imgui_io.Framerate);

        ImGui::End();
    }
}
