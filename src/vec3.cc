#include "vec3.hh"

#include <cmath>

namespace cr3on_rt {

Vec3::Vec3(float cx, float cy, float cz) : x(cx), y(cy), z(cz) {}

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3 Vec3::get_normalized() {
  float length = get_length();
  return Vec3(x / length, y / length, z / length);
}

float Vec3::get_length() {
  return sqrtf(get_squared_length());
}

float Vec3::get_squared_length() {
  return x * x + y * y + z * z;
}

Vec3 Vec3::operator-(Vec3 other) {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator+(Vec3 other) {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator*(float scalar) {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator/(float scalar) {
  return Vec3(x / scalar, y / scalar, z / scalar);
}

Vec3 Vec3::operator*=(float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

float dot_product(Vec3 v1, Vec3 v2) {
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float cross_product(Vec3 v1, Vec3 v2) {
  throw std::exception("TODO Not Implemented");
}

std::ostream& operator<<(std::ostream& os, Vec3& v) {
  return os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
}

void test_vec3() {
  Vec3 v1 = Vec3(2, 2, 2);
  std::cout << "v1=" << v1 << std::endl;

  Vec3 v2 = Vec3(1, 2, 3);
  std::cout << "v2=" << v2 << std::endl;

  Vec3 sum = v1 + v2;

  std::cout << "v1+v2=" << sum << std::endl;
}

}  // namespace cr3on_rt_vec

