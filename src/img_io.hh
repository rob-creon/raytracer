#pragma once
#include <fstream>
#include <iostream>

namespace cr3on_rt {
void write_pixels_to_file(std::string filename, unsigned int width,
                          unsigned int height, unsigned char* img) {
  unsigned int width_in_bytes = width * 3;
  unsigned int image_data_size = 3 * width * height;
  unsigned int file_size = image_data_size + 54;

  #pragma warning(disable : 4333 838)
  unsigned char file_header[14] = {'B',                             // 0
                                   'M',                             // 1
                                   (unsigned char)(file_size),        // 2
                                   (unsigned char)(file_size >> 8),   // 3
                                   (unsigned char)(file_size >> 16),  // 4
                                   (unsigned char)(file_size >> 24),  // 5
                                   0,                               // 6
                                   0,                               // 7
                                   0,                               // 8
                                   0,                               // 9
                                   54,                              // 10
                                   0,                               // 11
                                   0,                               // 12
                                   0};                              // 13

  unsigned char info_header[40] = {40,
                                   0,
                                   0,
                                   0,
                                   (unsigned char)(width),
                                   (unsigned char)(width >> 8),
                                   (unsigned char)(width >> 16),
                                   (unsigned char)(width >> 24),
                                   (unsigned char)(height),
                                   (unsigned char)(height >> 8),
                                   (unsigned char)(height >> 16),
                                   (unsigned char)(height >> 24),
                                   1,
                                   0,
                                   24,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0};
  #pragma warning(default : 4333 838)
  unsigned char padding[3] = {0, 0, 0};
  unsigned int padding_size = (4 - (width_in_bytes % 4)) % 4;

  FILE* file = std::fopen(filename.c_str(), "wb");
  fwrite(file_header, 1, sizeof(file_header) / sizeof(file_header[0]), file);
  fwrite(info_header, 1, sizeof(info_header) / sizeof(info_header[0]), file);
  for (unsigned int i = 0; i < height; i++) {
    fwrite(img + (i * width_in_bytes), 3, width, file);
    fwrite(padding, 1, padding_size, file);
  }

  fclose(file);
}
void test_rw_pixels() {
  const unsigned int width = 2, height = 2;
  const unsigned char img[width][height][3] = {{{0, 255, 0}, {127, 0, 127}},
                                               {{255, 0, 0}, {0, 0, 255}}};

  write_pixels_to_file("test.bmp", width, height, (unsigned char*)img);
}
}  // namespace cr3on_rt_imgwriter