#ifndef __HELPER3D_AFIN_H__
#define __HELPER3D_AFIN_H__

#include <glm/mat4x4.hpp>

namespace s21 {
class Afin {
 public:
  static glm::mat3 ScaleMtx(const glm::vec3& scale);

  static glm::mat3 RotateMtx(const glm::vec3& rotation);

  static void TranslateMtx(glm::mat4x4& mtx, const glm::vec3& translation);

  static glm::mat4 ModelMtx(glm::vec3 scale, glm::vec3 rotation,
                            glm::vec3 translation);
};
}  // namespace s21

#endif  // __HELPER3D_AFIN_H__