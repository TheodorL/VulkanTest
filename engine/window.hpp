#pragma once
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include "basic_types.hpp"
namespace ts {

class Window {
 public:
  Window();
  Window(const uint32_t width, const uint32_t height, const char* title);
  ~Window();

  bool hasResized() { return windowResized; }
  void resizeHandled() { windowResized = false; }
  glm::dvec2 getCursorDelta();
  GLFWwindow* getHandle() { return handle; }
  Keys getKeys();

 private:
  void checkInit();
  void updateKey(bool& key, const int action);
  static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
  static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

  bool captureCursor = false;
  bool cursorUpdated = false;
  glm::dvec2 prevCursorPos = glm::dvec2(0.0);
  glm::dvec2 cursorPos = glm::dvec2(0.0);
  Keys keys{};
  static Window* pThis;
  bool windowResized = false;
  static bool init;
  static uint32_t count;
  GLFWwindow* handle;
};

}  // namespace ts
