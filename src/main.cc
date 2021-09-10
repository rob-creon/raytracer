#include "camera.h"
#include "img_writer.hh"
#include "scene.hh"

const unsigned int camera_width = 1920;
const unsigned int camera_height = 1080;
const unsigned int max_recursion_level = 3;
const unsigned int msaa = 100;

using namespace cr3on_rt;

Color render_pixel(int x, int y, Camera camera, Scene scene) {
  Vec3 intersection = Vec3(0, 0, 0);
  Color pixel_color = Color(0, 0, 0);

  for (int sample = 0; sample < msaa; ++sample) {
    float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    Ray ray = camera.generate_ray(
        float(x) / float(camera_width) + r1 / camera_width,
        float(y) / float(camera_height) + r2 / camera_height);

    for (int object_index = 0; object_index < scene.objects.size();
         ++object_index) {
      if (scene.objects[object_index]->intersect(ray, intersection)) {
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

void render(Camera camera, Scene scene) {
  auto img = new unsigned char[camera_height][camera_width][3];

  unsigned int img_size = camera_width * camera_height;
  float last_progress = -.1;
  for (int j = 0; j < camera_height; ++j) {
    for (int i = 0; i < camera_width; ++i) {
      Color pixel_color = render_pixel(i, j, camera, scene);

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

int main() {
  Camera camera = Camera(camera_width, camera_height);

  Sphere* sphere1 = new Sphere(Vec3(0, 0, -3), 0.5, Color(1.0, 0, 0));
  Sphere* sphere2 = new Sphere(Vec3(1, 0, -3), 0.25, Color(0.5, 0.3, 0.7));

  Light light = Light(Vec3(-100, -100, -100), Color(1.0, 1.0, 1.0), 1);

  Scene scene{};
  scene.objects.push_back((Object*)sphere1);
  scene.objects.push_back((Object*)sphere2);
  scene.lights.push_back(light);

  render(camera, scene);

  delete sphere1;
  delete sphere2;

  return 0;
}
