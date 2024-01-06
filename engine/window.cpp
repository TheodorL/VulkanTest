#include "window.hpp"

#include <iostream>
#include <stdexcept>

using namespace ts;
#define CONST_BOOL 10
bool Window::init = false;
Window* Window::pThis = nullptr;
uint32_t Window::count = 0;

Window::Window() {
  checkInit();
  handle = nullptr;
}

Window::Window(const uint32_t width, const uint32_t height, const char* title) {
  checkInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
  Window::pThis = this;
  // glfwSetWindowUserPointer(handle, this);
  glfwSetFramebufferSizeCallback(handle, framebufferResizeCallback);
  glfwSetKeyCallback(handle, keyCallback);
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

Keys Window::getKeys() {
  return keys;
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
  // auto pThis = reinterpret_cast<Window*>(window);
  auto pThis = Window::pThis;
  pThis->windowResized = true;
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  // auto pThis = reinterpret_cast<Window*>(window);
  auto pThis = Window::pThis;

  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    pThis->keys.up = true;
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    pThis->keys.down = true;
  }
  if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    pThis->keys.left = true;
  }
  if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    pThis->keys.right = true;
  }
  if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
    pThis->keys.up = false;
  }
  if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
    pThis->keys.down = false;
  }
  if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
    pThis->keys.left = false;
  }
  if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
    pThis->keys.right = false;
  }
}
