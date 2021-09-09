#include "img_writer.hh"
#include "object.hh"

const unsigned camera_img_width = 300;
const unsigned camera_img_height = 300;

void render(cr3on_rt::Object* scene[]) {
  for (int j = 0; j < camera_img_height; ++j) {
    for (int i = 0; i < camera_img_width; ++i) {
    }
  }
}

int main() {
  cr3on_rt::test_vec3();
  render({});
}
