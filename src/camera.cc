#include "camera.h"

namespace cr3on_rt {
Camera::Camera(unsigned int iwidth, unsigned int iheight) {
  float width = float(iwidth);
  float height = float(iheight);
  this->horizontal = Vec3(2, 0, 0);
  this->vertical = Vec3(0, height * (2/width), 0);
  this->bottom_left = Vec3(-horizontal.x/2.0, -vertical.y/2.0, -1);
  this->origin = Vec3(0, 0, 0);
}
Ray Camera::generate_ray(float u, float v) {
  Vec3 ray_dir = bottom_left + (horizontal * u) + (vertical * v) - origin;
  return Ray(ray_dir.get_normalized(), this->origin);
}
}  // namespace cr3on_rt