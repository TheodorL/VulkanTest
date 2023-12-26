#include <GLFW/glfw3.h>

#include <stdexcept>

namespace ts {

class Window {
 public:
  Window();
  Window(const uint32_t width, const uint32_t height, const char* title);
  ~Window();

  bool hasResized() { return windowResized; }
  void resizeHandled() { windowResized = false; }

  GLFWwindow* getHandle() { return handle; }

 private:
  void checkInit();
  static void framebufferResizeCallback(GLFWwindow * window, int width, int height);

  bool windowResized = false;
  static bool init;
  static uint32_t count;
  GLFWwindow* handle;
};

}  // namespace ts