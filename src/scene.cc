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

  float a = dot_product(u, u);  // u.get_squared_length();
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

Vec3 Sphere::normal(Vec3 intersection) {
  return (intersection - this->pos).get_normalized();
}

Plane::Plane(Vec3 pos, Vec3 norm, Color color) {
  this->pos = pos;
  this->norm = norm;
  this->color = color;
}
bool Plane::intersect(Ray ray, Vec3& intersection) {
  float denom = dot_product(ray.dir, norm);
  if (denom == 0) return false;
  float numer = dot_product(pos - ray.origin, norm);
  float d = numer / denom;
  if (d < 0) {
    return false;
  } else {
    intersection = ray.origin + (ray.dir * d);
    return true;
  }
}
Vec3 Plane::normal(Vec3 intersection) { return norm; }
}  // namespace cr3on_rt