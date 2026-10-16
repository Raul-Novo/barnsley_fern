// cl /nologo /std:c17 /W4 /utf-8 /O2 barnsley_fern.c /Fe:barnsley_fern.exe
// .\barnsley_fern.exe
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

enum {
  FERN_WIDTH = 64,
  FERN_HEIGHT = 64,
  ITERATION_COUNT = 30000
};

int main(void) {
  char canvas[FERN_HEIGHT][FERN_WIDTH] = {{0}};
  uint32_t random_state = 1u;
  double point_x = 0.0;
  double point_y = 0.0;

  for (size_t iteration = 0; iteration < ITERATION_COUNT; ++iteration) {
    random_state = (random_state * 1664525u) + 1013904223u;
    uint32_t random_percent = (random_state >> 16u) % 100u;

    double next_x = 0.0;
    double next_y = 0.0;

    if (random_percent < 1u) {
      next_x = 0.0;
      next_y = 0.16 * point_y;
    } else if (random_percent < 86u) {
      next_x = (0.85 * point_x) + (0.04 * point_y);
      next_y = (-0.04 * point_x) + (0.85 * point_y) + 1.6;
    } else if (random_percent < 93u) {
      next_x = (0.20 * point_x) - (0.26 * point_y);
      next_y = (0.23 * point_x) + (0.22 * point_y) + 1.6;
    } else {
      next_x = (-0.15 * point_x) + (0.28 * point_y);
      next_y = (0.26 * point_x) + (0.24 * point_y) + 0.44;
    }

    point_x = next_x;
    point_y = next_y;

    double column_fraction = (point_x + 2.2) / 4.9;
    double row_fraction = (10.0 - point_y) / 10.0;

    if (column_fraction < 0.0 || column_fraction >= 1.0 || row_fraction < 0.0 ||
        row_fraction >= 1.0) {
      continue;
    }

    size_t column = (size_t)(column_fraction * (double)FERN_WIDTH);
    size_t row = (size_t)(row_fraction * (double)FERN_HEIGHT);
    canvas[row][column] = '#';
  }

  for (size_t row = 0; row < FERN_HEIGHT; ++row) {
    for (size_t column = 0; column < FERN_WIDTH; ++column) {
      if (putchar(canvas[row][column] ? '#' : ' ') == EOF) {
        return 1;
      }
    }

    if (putchar('\n') == EOF) {
      return 1;
    }
  }

  return ferror(stdout) ? 1 : 0;
}
