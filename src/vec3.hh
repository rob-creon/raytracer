#pragma once
#include <iostream>

namespace cr3on_rt {
class Vec3 {
 public:
  float x, y, z;
  Vec3();
  Vec3(float x, float y, float z);
  Vec3 get_normalized();
  float get_length();
  float get_squared_length();
  Vec3 operator-(Vec3 other);
  Vec3 operator+(Vec3 other);
  Vec3 operator*(float scalar);
  Vec3 operator/(float scalar);
  Vec3 operator*=(float scalar);

  static void test_vec3();
};

float dot_product(Vec3 v1, Vec3 v2);
float cross_product(Vec3 v1, Vec3 v2);
std::ostream& operator<<(std::ostream& os, Vec3& v);

void test_vec3();

}  // namespace cr3on_rt_vec