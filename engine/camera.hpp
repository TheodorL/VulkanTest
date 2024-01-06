#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ts {

class Camera {
 public:
  Camera(float fov, float aspect, float znear, float zfar);
  ~Camera();

  bool moving();
  void update(float deltaTime);
  void setPosition(glm::vec3 position);

  struct {
    glm::mat4 perspective;
    glm::mat4 view;
  } matrices;

  struct {
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
  } keys;

 private:
  float fov;
  float znear, zfar;
  float translationSpeed = 0.4f;

  glm::vec3 position = glm::vec3();
  glm::vec3 rotation = glm::vec3();

  void updateViewMatrix();
};

}  // namespace ts