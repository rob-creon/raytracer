#include "camera.h"
#include "img_writer.hh"
#include "scene.hh"

const unsigned int camera_width = 1920;
const unsigned int camera_height = 1080;

using namespace cr3on_rt;

Color render_pixel(int i, int j, Camera camera, Scene scene) {
  Vec3 intersection = Vec3(0, 0, 0);
  Color pixel_color = Color(0, 0, 0);

  Ray ray = camera.generate_ray(float(i) / float(camera_width),
                                float(j) / float(camera_height));

  for (int i = 0; i < scene.objects.size(); ++i) {
    if (scene.objects[i]->intersect(ray, intersection)) {
      pixel_color = scene.objects[i]->color;
    }
  }
  return pixel_color;
}

void render(Camera camera, Scene scene) {
  auto img = new unsigned char[camera_height][camera_width][3];

  unsigned int img_size = camera_width * camera_height;
  float last_progress = -.1;
  for (int j = 0; j < camera_height; ++j) {
    for (int i = 0; i < camera_width; ++i) {
      Color pixel_color = render_pixel(i, j, camera, scene);

      img[j][i][2] = pixel_color.r;
      img[j][i][1] = pixel_color.g;
      img[j][i][0] = pixel_color.b;

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

  Scene scene{};
  
  Sphere* sphere1 = new Sphere(Vec3(0, 0, -3), 0.5, Color(255, 0, 0));
  Sphere* sphere2 = new Sphere(Vec3(1, 0, -3), 0.25, Color(0, 255, 0));
  
  scene.objects.push_back((Object*)sphere1);
  scene.objects.push_back((Object*)sphere2);

  render(camera, scene);

  delete sphere1;
  delete sphere2;

  return 0;
}
