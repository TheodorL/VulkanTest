#pragma once
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/glm.hpp>
namespace ts {

struct Keys {
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool shift = false;
};

class Window {
 public:
  Window();
  Window(const uint32_t width, const uint32_t height, const char* title);
  ~Window();

  bool hasResized() { return windowResized; }
  void resizeHandled() { windowResized = false; }

  GLFWwindow* getHandle() { return handle; }
  Keys getKeys();

 private:
  void checkInit();
  void updateKey(bool& key, const int action);
  static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
  static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

  glm::dvec2 prevCursorPos;
  Keys keys{};
  static Window* pThis;
  bool windowResized = false;
  static bool init;
  static uint32_t count;
  GLFWwindow* handle;
};

}  // namespace ts
