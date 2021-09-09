#include "object.hh"

namespace cr3on_rt {

Sphere::Sphere(double r) : radius(r) {}

bool Sphere::intersect(Ray ray, Vec3<>& intersection) { return false; }
}  // namespace cr3on_rt