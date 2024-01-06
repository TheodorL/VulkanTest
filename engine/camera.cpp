#include "camera.hpp"

#include <iostream>

namespace ts {

Camera::Camera(float fov, float aspect, float znear, float zfar) {
  this->fov = fov;
  this->znear = znear;
  this->zfar = zfar;
  matrices.perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
  matrices.perspective[1][1] *= -1;
}

void Camera::updateViewMatrix() {
  glm::mat4 rotationMatrix = glm::mat4(1.0f);
  glm::mat4 transformationMatrix;

  rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

  transformationMatrix = glm::translate(glm::mat4(1.0f), position);

  matrices.view = rotationMatrix * transformationMatrix;
}

void Camera::update(float deltaTime) {
  if (moving()) {
    glm::vec3 front;
    front.x = -cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
    front.y = sin(glm::radians(rotation.x));
    front.z = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    front = glm::normalize(front);
    float moveSpeed = deltaTime * translationSpeed;

    if (keys.up) {
      position += front * moveSpeed;
    }
    if (keys.down) {
      position -= front * moveSpeed;
    }
    if (keys.left) {
      position -= glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))) * moveSpeed;
    }
    if (keys.right) {
      position += glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))) * moveSpeed;
    }

    updateViewMatrix();
  }
}

bool Camera::moving() {
  return (keys.up || keys.down || keys.left || keys.right);
}

}  // namespace ts