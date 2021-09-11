#include <limits>

#include "camera.h"
#include "img_writer.hh"
#include "scene.hh"

const unsigned int camera_width = 1920;
const unsigned int camera_height = 1080;
const unsigned int max_recursion_level = 3;
const unsigned int msaa = 100;
const float epsilon = 0.00001;