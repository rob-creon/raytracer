#pragma once
#include "vec3.hh"

namespace cr3on_rt {
class Ray {
 public:
  Ray(Vec3 d, Vec3 o);
  Vec3 dir;
  Vec3 origin;
};
}  // namespace cr3on_rt
