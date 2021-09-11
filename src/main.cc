#include "camera.h"
#include "img_writer.hh"
#include "scene.hh"

const unsigned int camera_width = 1920;
const unsigned int camera_height = 1080;
const unsigned int max_recursion_level = 3;
const unsigned int msaa = 100;

cr3on_rt::Color render_pixel(int x, int y, cr3on_rt::Camera camera,
                             cr3on_rt::Scene scene) {
  cr3on_rt::Vec3 intersection = cr3on_rt::Vec3(0, 0, 0);
  cr3on_rt::Color pixel_color = cr3on_rt::Color(0, 0, 0);

  for (int sample = 0; sample < msaa; ++sample) {
    float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    cr3on_rt::Ray camera_ray = camera.generate_ray(
        float(x) / float(camera_width) + r1 / camera_width,
        float(y) / float(camera_height) + r2 / camera_height);

    for (int object_index = 0; object_index < scene.objects.size();
         ++object_index) {
      if (scene.objects[object_index]->intersect(camera_ray, intersection)) {
        pixel_color.r += scene.objects[object_index]->color.r;
        pixel_color.g += scene.objects[object_index]->color.g;
        pixel_color.b += scene.objects[object_index]->color.b;
      }
    }
  }
  pixel_color.r /= (float)msaa;
  pixel_color.g /= (float)msaa;
  pixel_color.b /= (float)msaa;
  return pixel_color;
}

void render(cr3on_rt::Camera camera, cr3on_rt::Scene scene) {
  auto img = new unsigned char[camera_height][camera_width][3];

  unsigned int img_size = camera_width * camera_height;
  float last_progress = -.1;
  for (int j = 0; j < camera_height; ++j) {
    for (int i = 0; i < camera_width; ++i) {
      cr3on_rt::Color pixel_color = render_pixel(i, j, camera, scene);

      img[j][i][2] = unsigned char(std::min(pixel_color.r * 255.0, 255.0));
      img[j][i][1] = unsigned char(std::min(pixel_color.g * 255.0, 255.0));
      img[j][i][0] = unsigned char(std::min(pixel_color.b * 255.0, 255.0));

      unsigned int progress = j * camera_width + camera_height;
      float progressf = (float)progress / (float)img_size;
      if (progressf - .05 > last_progress) {
        printf("Tracing %2.0f%% complete...\n", progressf * 100);
        last_progress = progressf;
      }
    }
  }
  cr3on_rt::write_pixels_to_file("../out/output.bmp", camera_width,
                                 camera_height, (unsigned char*)img);
  delete (img);
}

using namespace cr3on_rt;

int main() {
  Camera camera = Camera(camera_width, camera_height);
  
  Scene scene{};
  scene.objects.push_back(
      (Object*)new Sphere(Vec3(0, 0, -3), 0.5, Color(1.0, 0, 0)));
  scene.objects.push_back(
      (Object*)new Sphere(Vec3(1, 0, -3), 0.25, Color(0.5, 0.3, 0.7)));
  scene.lights.push_back(Light(Vec3(-100, -100, -100), Color(1.0, 1.0, 1.0), 1));

  render(camera, scene);

  return 0;
}
