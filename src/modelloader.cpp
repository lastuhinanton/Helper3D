#include <Helper3D/except.h>
#include <Helper3D/modelloader.h>

#include <cstdio>
#include <fstream>

namespace s21 {
#define LINE_TYPE_VEC 'v'
#define LINE_TYPE_TEX 't'
#define LINE_TYPE_FACE 'f'

glm::vec3 ReadPositionOrThrow(const char* lineRaw) {
  glm::vec3 position;
  if (std::sscanf(lineRaw, "v %f %f %f", &position.x, &position.y,
                  &position.z) == 3) {
    return position;
  } else {
    throw modelloader_error("Can't read position");
  }
}

glm::vec2 ReadTexCoordOrThrow(const char* lineRaw) {
  glm::vec2 texCoord;
  if (std::sscanf(lineRaw, "vt %f %f", &texCoord.x, &texCoord.y) == 2) {
    return texCoord;
  } else {
    throw modelloader_error("Can't read position");
  }
}

const char* ReadVertexOrThrow(const char* strRaw, Vertex& vertex,
                              std::vector<glm::vec3>& positions,
                              std::vector<glm::vec2>& texCoords) {
  ptrdiff_t positionIdx = -1;
  ptrdiff_t texCoordIdx = -1;
  ptrdiff_t normalIdx = -1;

  int numLength = 0;

  if (strRaw == nullptr) return nullptr;

  while (isspace(*strRaw)) strRaw += 1;
  if (strRaw[0] == '\0') return nullptr;

  if (std::sscanf(strRaw, "%zd%n", &positionIdx, &numLength) == 1) {
    strRaw += numLength;
  } else {
    throw modelloader_error("OBJ read face error");
  }

  if (strRaw[0] == '/') {
    strRaw += 1;
    std::sscanf(strRaw, "%zd%n", &texCoordIdx, &numLength);
    strRaw += numLength;
  }

  if (strRaw[0] == '/') {
    strRaw += 1;
    std::sscanf(strRaw, "%zd%n", &normalIdx, &numLength);
    strRaw += numLength;
  }

  if (positionIdx != -1) {
    vertex.position = positions[static_cast<size_t>(positionIdx) - 1];
  }

  if (texCoordIdx != -1) {
    vertex.texCoord = texCoords[static_cast<size_t>(texCoordIdx) - 1];
  }

  return strRaw;
}

void ReadFaceOrThrow(const char* lineRaw, std::vector<Vertex>& vertices,
                     std::vector<glm::vec3>& positions,
                     std::vector<glm::vec2>& texCoords) {
  Vertex firstVtx;
  Vertex secondVtx;
  Vertex thirdVtx;

  lineRaw += 1;

  lineRaw = ReadVertexOrThrow(lineRaw, firstVtx, positions, texCoords);
  lineRaw = ReadVertexOrThrow(lineRaw, secondVtx, positions, texCoords);
  lineRaw = ReadVertexOrThrow(lineRaw, thirdVtx, positions, texCoords);
  vertices.push_back(firstVtx);
  vertices.push_back(secondVtx);
  vertices.push_back(thirdVtx);

  Vertex tmpVtx;
  while ((lineRaw = ReadVertexOrThrow(lineRaw, tmpVtx, positions, texCoords)) !=
         nullptr) {
    secondVtx = thirdVtx;
    thirdVtx = tmpVtx;

    vertices.push_back(firstVtx);
    vertices.push_back(secondVtx);
    vertices.push_back(thirdVtx);
  }
}

std::vector<Vertex> ModelLoader::LoadObjOrThrow(const char* filename) {
  std::ifstream objStream(filename);

  if (!objStream.is_open()) {
    throw modelloader_error("OBJ file does not exist");
  }

  std::vector<Vertex> vertices;
  std::vector<glm::vec3> positions;
  std::vector<glm::vec2> texCoords;

  for (std::string lineStr; std::getline(objStream, lineStr);) {
    char lineType = lineStr[0];
    if (lineType == LINE_TYPE_VEC && isalpha(lineStr[1])) {
      lineType = lineStr[1];
    }

    switch (lineType) {
      case LINE_TYPE_VEC:
        positions.push_back(ReadPositionOrThrow(lineStr.c_str()));
        break;

      case LINE_TYPE_TEX:
        texCoords.push_back(ReadTexCoordOrThrow(lineStr.c_str()));
        break;

      case LINE_TYPE_FACE:
        ReadFaceOrThrow(lineStr.c_str(), vertices, positions, texCoords);
        break;
    }
  }

  return vertices;
}
}  // namespace s21