#include "camera.h"
#include "img_io.hh"
#include "scene.hh"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define TOTAL_NUM_PIXELS SCREEN_WIDTH *SCREEN_HEIGHT
#define MSAA_SAMPLES 100
#define MAX_RECURSION_DEPTH 5
#define EPSILON 0.00001
//#define INFINITY 3.402823466e+38F

using namespace cr3on_rt;

struct Collision {
  Object *obj;
  float distance_squared;
  Vec3 intersection;
};

Collision get_first_collision(Scene scene, Ray &ray) {
  Collision first_collision{};
  first_collision.distance_squared = INFINITY;
  for (int i = 0; i < scene.objects.size(); ++i) {
    Vec3 intersection = Vec3();
    Object *object = scene.objects[i];
    if (object->intersect(ray, intersection)) {
      float distance_squared = (intersection - ray.origin).get_squared_length();
      if (distance_squared < first_collision.distance_squared) {
        first_collision.obj = object;
        first_collision.intersection = intersection;
        first_collision.distance_squared = distance_squared;
      }
    }
  }
  return first_collision;
}

bool collides(Scene scene, Ray &ray) {
  Vec3 unused = Vec3();
  for (int i = 0; i < scene.objects.size(); ++i) {
    if (scene.objects[i]->intersect(ray, unused)) {
      return true;
    }
  }
  return false;
}

Color trace(Scene scene, Ray &ray, int depth) {
  Collision collision = get_first_collision(scene, ray);
  if (collision.obj == nullptr) return Color(0, 0, 0);
  Vec3 norm = collision.obj->normal(collision.intersection);
  Ray reflected_ray = Ray(norm, collision.intersection + (norm * EPSILON));
  if (depth < MAX_RECURSION_DEPTH) {
    float facingratio = -dot_product(ray.dir, norm);
    float one_minus_fr = 1 - facingratio;
    float fresnel =
        0.1 * (one_minus_fr * one_minus_fr * one_minus_fr) + 0.9 * (0.1);
    Color reflection = trace(scene, reflected_ray, depth + 1);
    Color surface = collision.obj->color(collision.intersection);
    Color mixed{};
    mixed.r = reflection.r * fresnel + surface.r * (1.0 - fresnel);
    mixed.g = reflection.g * fresnel + surface.g * (1.0 - fresnel);
    mixed.b = reflection.b * fresnel + surface.b * (1.0 - fresnel);
    return mixed;
  } else {
    bool is_shadow = collides(scene, reflected_ray);
    return is_shadow ? Color(0, 0, 0)
                     : collision.obj->color(collision.intersection);
  }
}

void render(Camera camera, Scene scene) {
  auto img = new unsigned char[SCREEN_HEIGHT][SCREEN_WIDTH][3];
  for (int v = 0; v < SCREEN_HEIGHT; ++v) {
    printf("%f%% rendered\n", 100.0 * float(v) / float(SCREEN_HEIGHT));
    for (int u = 0; u < SCREEN_WIDTH; ++u) {
      Color pixel_avg_color = Color{0, 0, 0};
      for (int sample_ctr = 0; sample_ctr < MSAA_SAMPLES; ++sample_ctr) {
        float msaa_ru = 0;
        float msaa_rv = 0;
        if (MSAA_SAMPLES > 1) {
          msaa_ru = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
          msaa_rv = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        }

        Ray ray =
            camera.generate_ray((float(u) + msaa_ru) / float(SCREEN_WIDTH),
                                (float(v) + msaa_rv) / float(SCREEN_HEIGHT));

        cr3on_rt::Color ray_color = trace(scene, ray, 0);
        pixel_avg_color.r += ray_color.r / float(MSAA_SAMPLES);
        pixel_avg_color.g += ray_color.g / float(MSAA_SAMPLES);
        pixel_avg_color.b += ray_color.b / float(MSAA_SAMPLES);
      }
      img[v][u][2] = unsigned char(std::min(pixel_avg_color.r * 255.0, 255.0));
      img[v][u][1] = unsigned char(std::min(pixel_avg_color.g * 255.0, 255.0));
      img[v][u][0] = unsigned char(std::min(pixel_avg_color.b * 255.0, 255.0));
    }
  }
  cr3on_rt::write_pixels_to_file("../out/output2.bmp", SCREEN_WIDTH,
                                 SCREEN_HEIGHT, (unsigned char *)img);
}

int main() {
  Camera camera = Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

  Scene scene{};
  scene.objects.push_back(
      (Object *)new Plane(Vec3(0, -0.5, 0), Vec3(0, 1, 0), Color(0.5, 0.2, 0)));
  scene.objects.push_back(
      (Object *)new Sphere(Vec3(-1.8, 0.2, -3), 0.7, Color(0.1, 0, 0)));
  scene.objects.push_back(
      (Object *)new Sphere(Vec3(1.4, 1.5, -6), 2, Color(0.5, 0.3, 0.7)));
  scene.objects.push_back(
      (Object *)new Sphere(Vec3(0, 0.2, -3.3), 0.7, Color(0.5, 0.8, 0.0)));
  scene.objects.push_back(
      (Object *)new Sphere(Vec3(1.8, -0.2, -2.3), 0.3, Color(0, 0.3, 1.0)));

  scene.lights.push_back(
      Light(Vec3(-100, -100, -100), Color(1.0, 1.0, 1.0), 1));

  render(camera, scene);

  return 0;
}