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
  glfwSetCursorPosCallback(handle, cursorPositionCallback);
  glfwSetMouseButtonCallback(handle, mouseButtonCallback);
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

void Window::updateKey(bool& key, const int action) {
  // TODO profile reference access vs copy+access performance
  if (action == GLFW_PRESS) {
    key = true;
  } else if (action == GLFW_RELEASE) {
    key = false;
  }
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  // auto pThis = reinterpret_cast<Window*>(window);
  auto pThis = Window::pThis;

  switch (key) {
    case GLFW_KEY_LEFT_SHIFT:
      pThis->updateKey(pThis->keys.shift, action);
      break;
    case GLFW_KEY_W:
    case GLFW_KEY_UP:
      pThis->updateKey(pThis->keys.up, action);
      break;
    case GLFW_KEY_S:
    case GLFW_KEY_DOWN:
      pThis->updateKey(pThis->keys.down, action);
      break;
    case GLFW_KEY_A:
    case GLFW_KEY_LEFT:
      pThis->updateKey(pThis->keys.left, action);
      break;
    case GLFW_KEY_D:
    case GLFW_KEY_RIGHT:
      pThis->updateKey(pThis->keys.right, action);
      break;
    default:
      break;
  }
}

void Window::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
  pThis->prevCursorPos.x = xpos;
  pThis->prevCursorPos.y = ypos;
  std::cout << pThis->prevCursorPos.x << " " << pThis->prevCursorPos.y << '\n';
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}
