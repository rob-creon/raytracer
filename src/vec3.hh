#pragma once
#include <iostream>

namespace cr3on_rt_vec {
template <typename T=float>
class Vec3 {
 public:
  T x, y, z;
  Vec3();
  Vec3(T x, T y, T z);
  Vec3<T> get_normalized();
  T get_length();
  T get_squared_length();
  Vec3<T> operator-(Vec3<T> other);
  Vec3<T> operator+(Vec3<T> other);
  Vec3<T> operator*(T scalar);
  Vec3<T> operator/(T scalar);
  Vec3<T> operator*=(T scalar);

  static void test_vec3();
};

template <typename T>
T dot_product(Vec3<T> v1, Vec3<T> v2);

template <typename T>
T cross_product(Vec3<T> v1, Vec3<T> v2);

template <typename T>
std::ostream& operator<<(std::ostream& os, Vec3<T>& v);

void test_vec3();

}  // namespace cr3on_rt_vec