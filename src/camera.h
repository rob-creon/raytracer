#pragma once
#include "ray.hh"

namespace cr3on_rt {
class Camera {
 public:
  Camera(unsigned int width, unsigned int height);
  Ray generate_ray(float u, float v);

 private:
  Vec3 bottom_left;
  Vec3 horizontal;
  Vec3 vertical;
  Vec3 origin;
};
}  // namespace cr3on_rt