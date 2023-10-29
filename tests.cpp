#include "libs/afin.h"
#include "libs/except.h"
#include "libs/modelloader.h"
#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define PATH_MODELS "../../"

#define EPS 1e-7

void TestVtx(s21::Vertex orig, s21::Vertex test) {
  EXPECT_EQ(orig.position.x, test.position.x);
  EXPECT_EQ(orig.position.y, test.position.y);
  EXPECT_EQ(orig.position.z, test.position.z);
  EXPECT_EQ(orig.texCoord.x, test.texCoord.x);
  EXPECT_EQ(orig.texCoord.y, test.texCoord.y);
}

TEST(Load, Test1) {
  std::vector<s21::Vertex> vtxVec =
      s21::ModelLoader::LoadObjOrThrow(PATH_MODELS "Resources/Models/test.3d");

  TestVtx(vtxVec[0], (s21::Vertex){{0.5f, 0.0f, 0.5f}, {0.0f, 0.0f}});
  TestVtx(vtxVec[1], (s21::Vertex){{1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}});
  TestVtx(vtxVec[2], (s21::Vertex){{0.3f, 0.123f, 0.3f}, {1.0f, 1.0f}});
}

TEST(Load, Test2) {
  EXPECT_THROW(s21::ModelLoader::LoadObjOrThrow(PATH_MODELS
                                                "Resources/Models/test_err.3d"),
               s21::modelloader_error);
}

TEST(Load, Test3) {
  EXPECT_THROW(s21::ModelLoader::LoadObjOrThrow(
                   PATH_MODELS "Resources/Models/test_unknown.3d"),
               s21::modelloader_error);
}

TEST(Load, TestBig) {
  std::vector<s21::Vertex> vtxVec = s21::ModelLoader::LoadObjOrThrow(
      PATH_MODELS "Resources/Models/backpack.3d");

  EXPECT_FALSE(vtxVec.empty());
  EXPECT_TRUE(vtxVec.size() > 10000);
}

TEST(Afin, Test1) {
  glm::vec4 testVec(-2.0f, 0.0f, 0.0f, 1.0f);

  glm::mat4 modelMtx = s21::Afin::ModelMtx(glm::vec3(1.0f), glm::vec3(),
                                           glm::vec3(3.0f, 2.0f, 0.0f));

  testVec = modelMtx * testVec;

  EXPECT_FLOAT_EQ(testVec.x, 1.0f);
  EXPECT_FLOAT_EQ(testVec.y, 2.0f);
  EXPECT_FLOAT_EQ(testVec.z, 0.0f);
}

TEST(Afin, Test2) {
  glm::vec4 testVec(-2.0f, 0.0f, 0.0f, 1.0f);

  glm::mat4 modelMtx = s21::Afin::ModelMtx(
      glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3());

  testVec = modelMtx * testVec;

  EXPECT_TRUE(std::fabs(testVec.x - 0.0f) < EPS);
  EXPECT_TRUE(std::fabs(testVec.y - -2.0f) < EPS);
  EXPECT_TRUE(std::fabs(testVec.z - 0.0f) < EPS);
}

TEST(Afin, Test3) {
  glm::vec4 testVec(2.0f, 1.0f, 0.5f, 1.0f);

  glm::mat4 modelMtx = s21::Afin::ModelMtx(glm::vec3(1.5f, 3.0f, 6.0f),
                                           glm::vec3(), glm::vec3());

  testVec = modelMtx * testVec;

  EXPECT_FLOAT_EQ(testVec.x, 3.0f);
  EXPECT_FLOAT_EQ(testVec.y, 3.0f);
  EXPECT_FLOAT_EQ(testVec.z, 3.0f);
}