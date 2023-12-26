#include "Window.hpp"

using namespace ts;

bool Window::init = false;
uint32_t Window::count = 0;

Window::Window() {
  checkInit();
  handle = nullptr;
}

Window::Window(const uint32_t width, const uint32_t height, const char* title) {
  checkInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
  glfwSetWindowUserPointer(handle, this);
  glfwSetFramebufferSizeCallback(handle, framebufferResizeCallback);
}

Window::~Window() {
  Window::count--;
  if (handle != nullptr) {
    glfwDestroyWindow(handle);
  }
  if (Window::count == 0) {
    glfwTerminate();
  }

}

void Window::checkInit() {
  if (Window::init == false) {
    if (glfwInit() != GLFW_TRUE) {
      throw std::runtime_error("Failed to initialize GLFW!");
    }
    Window::init = true;
  }
  Window::count++;
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
  auto pThis = reinterpret_cast<Window*>(window);
  pThis->windowResized = true;
}
