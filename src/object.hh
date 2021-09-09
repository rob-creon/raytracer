#pragma once
#include "ray.hh"

namespace cr3on_rt {
struct Color {
  unsigned char r, g, b;
};

class Object {
 public:
  Color color;
  virtual bool intersect(Ray ray, Vec3<>& intersection) = 0;
  
};

class Sphere : Object {
 public:
  Sphere(double radius);
  virtual bool intersect(Ray ray, Vec3<>& intersection);

 private:
  double radius;
};
}  // namespace cr3on_rt