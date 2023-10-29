#ifndef __MODELLOADER_MODELLOADER_H__
#define __MODELLOADER_MODELLOADER_H__

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace s21 {
struct Vertex {
  glm::vec3 position;
  glm::vec2 texCoord;
};

class ModelLoader {
 public:
  static std::vector<Vertex> LoadObjOrThrow(const char* filename);
};
}  // namespace s21

#endif  // __MODELLOADER_MODELLOADER_H__