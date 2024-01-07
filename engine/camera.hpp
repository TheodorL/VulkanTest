#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "basic_types.hpp"

namespace ts {

class Camera {
 public:
  Camera(float fov, float aspect, float znear, float zfar);
  ~Camera();

  bool moving();
  void update(float deltaTime);
  void processCursorMovement(glm::dvec2 delta);
  void setPosition(glm::vec3 position);

  struct {
    glm::mat4 perspective;
    glm::mat4 view;
  } matrices;

  Keys keys;

 private:
  float fov;
  float znear, zfar;
  float translationSpeed = 0.4f;
  glm::vec2 rotationSensitivity = glm::dvec2(0.5f, 0.5f);

  glm::vec3 position = glm::vec3();
  glm::vec3 rotation = glm::vec3();

  void updateViewMatrix();
};

}  // namespace ts