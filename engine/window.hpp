#pragma once
#include <GLFW/glfw3.h>

namespace ts {

struct Keys{
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
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
  static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  Keys keys{};
  static Window* pThis;
  bool windowResized = false;
  static bool init;
  static uint32_t count;
  GLFWwindow* handle;
};

}  // namespace ts
