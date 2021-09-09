#include "vec3.hh"

#include <cmath>

namespace cr3on_rt {
template <typename T>
Vec3<T>::Vec3(T cx, T cy, T cz) : x(cx), y(cy), z(cz) {}

template <typename T>
Vec3<T>::Vec3() : x(0), y(0), z(0) {}
template <typename T>
Vec3<T> Vec3<T>::get_normalized() {
  T length = get_length();
  return Vec3<T>(x / length, y / length, z / length);
}

template <typename T>
T Vec3<T>::get_length() {
  return (T)sqrt(get_squared_length());
}

template <typename T>
T Vec3<T>::get_squared_length() {
  return x * x + y * y + z * z;
}

template <typename T>
Vec3<T> Vec3<T>::operator-(Vec3<T> other) {
  return Vec3<T>(x - other.x, y - other.y, z - other.z);
}

template <typename T>
Vec3<T> Vec3<T>::operator+(Vec3<T> other) {
  return Vec3<T>(x + other.x, y + other.y, z + other.z);
}

template <typename T>
Vec3<T> Vec3<T>::operator*(T scalar) {
  return Vec3<T>(this.x * scalar, this.y * scalar, this.z * scalar);
}

template <typename T>
Vec3<T> Vec3<T>::operator/(T scalar) {
  return Vec3<T>(this.x / scalar, this.y / scalar, this.z / scalar);
}

template <typename T>
Vec3<T> Vec3<T>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return this;
}

template <typename T>
T dot_product(Vec3<T> v1, Vec3<T> v2) {
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

template <typename T>
T cross_product(Vec3<T> v1, Vec3<T> v2) {
  throw std::exception("TODO Not Implemented");
}

template <typename T>
std::ostream& operator<<(std::ostream& os, Vec3<T>& v) {
  return os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
}

}  // namespace cr3on_rt_vec

void cr3on_rt::test_vec3() {
  Vec3<> v1 = Vec3<>(2, 2, 2);
  std::cout << "v1=" << v1 << std::endl;

  Vec3<> v2 = Vec3<>(1, 2, 3);
  std::cout << "v2=" << v2 << std::endl;

  Vec3<> sum = v1 + v2;

  std::cout << "v1+v2=" << sum << std::endl;

}