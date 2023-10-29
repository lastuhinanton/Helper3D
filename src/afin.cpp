#include <Helper3D/afin.h>

#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>

namespace s21 {
glm::mat3x3 Afin::ScaleMtx(const glm::vec3& scale) {
  return glm::mat3(scale.x, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f,
                   scale.z);
}

glm::mat3x3 Afin::RotateMtx(const glm::vec3& rotation) {
  float x_radians = glm::radians(rotation.x);
  float y_radians = glm::radians(rotation.y);
  float z_radians = glm::radians(rotation.z);

  glm::mat3 rotateMtxX(1.0f);
  rotateMtxX[1][1] = cos(x_radians);
  rotateMtxX[2][1] = -sin(x_radians);
  rotateMtxX[1][2] = sin(x_radians);
  rotateMtxX[2][2] = cos(x_radians);

  glm::mat3 rotateMtxY(1.0f);
  rotateMtxY[0][0] = cos(y_radians);
  rotateMtxY[2][0] = sin(y_radians);
  rotateMtxY[0][2] = -sin(y_radians);
  rotateMtxY[2][2] = cos(y_radians);

  glm::mat3 rotateMtxZ(1.0f);
  rotateMtxZ[0][0] = cos(z_radians);
  rotateMtxZ[1][0] = -sin(z_radians);
  rotateMtxZ[0][1] = sin(z_radians);
  rotateMtxZ[1][1] = cos(z_radians);

  return rotateMtxZ * rotateMtxY * rotateMtxX;
}

void Afin::TranslateMtx(glm::mat4x4& mtx, const glm::vec3& translation) {
  mtx[3][0] = translation.x;
  mtx[3][1] = translation.y;
  mtx[3][2] = translation.z;
}

glm::mat4 Afin::ModelMtx(glm::vec3 scale, glm::vec3 rotation,
                         glm::vec3 translation) {
  glm::mat3 scaleMtx = ScaleMtx(scale);
  glm::mat3 rotateMtx = RotateMtx(rotation);

  glm::mat4 modelMtx = glm::mat4(rotateMtx * scaleMtx);
  TranslateMtx(modelMtx, translation);

  return modelMtx;
}
}  // namespace s21