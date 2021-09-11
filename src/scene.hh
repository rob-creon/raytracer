#pragma once
#include <vector>

#include "camera.h"
#include "ray.hh"

namespace cr3on_rt {
struct Color {
  float r, g, b;
};

class Light {
 public:
  Vec3 pos;
  Color color;
  float intensity;
  Light(Vec3 p, Color c, float i) {
    this->pos = p;
    this->color = c;
    this->intensity = i;
  }
};

class Object {
 public:
  Color color;
  Vec3 pos;
  virtual bool intersect(Ray ray, Vec3& intersection) = 0;
  virtual Vec3 normal(Vec3 intersection) = 0;
};

class Sphere : Object {
 public:
  Sphere(Vec3 pos, float radius, Color color);
  virtual bool intersect(Ray ray, Vec3& intersection);
  virtual Vec3 normal(Vec3 intersection);
 private:
  float radius;
};

struct Scene {
 public:
  std::vector<Light> lights;
  std::vector<Object*> objects;

  Scene() {
    lights = std::vector<Light>();
    objects = std::vector<Object*>();
  }
};
}  // namespace cr3on_rt