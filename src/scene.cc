#include "scene.hh"

#include "vec3.hh"

namespace cr3on_rt {

Sphere::Sphere(Vec3 cpos, float cr, Color color) {
  this->pos = cpos;
  this->radius = cr;
  this->color = color;
}

bool Sphere::intersect(Ray ray, Vec3& intersection) {
  Vec3 origin = ray.origin;
  Vec3 u = ray.dir;

  Vec3 center = pos;

  Vec3 oc = origin - center;

  float a = dot_product(u, u); //u.get_squared_length();
  float b = 2.0 * dot_product(u, oc);
  float c = oc.get_squared_length() - (radius * radius);

  float discriminant = (b * b) - 4.0 * (a * c);
  if (discriminant < 0) return false;

  float root = sqrtf(discriminant);

  float d1 = (-b + root) / (2 * a);
  float d2 = (-b - root) / (2 * a);

  if (d1 >= 0 && d2 >= 0) {
    intersection = ray.origin + (ray.dir * std::min(d1, d2));
    return true;
  } else if (d1 >= 0 && d2 < 0) {
    intersection = ray.origin + (ray.dir * d1);
    return true;
  } else if (d2 >= 0 && d1 < 0) {
    intersection = ray.origin + (ray.dir * d2);
    return true;
  } else {
    return false;
  }
}
}  // namespace cr3on_rt