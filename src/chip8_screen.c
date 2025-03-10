#include "chip8_screen.h"

#include <assert.h>
#include <memory.h>
#include <stdbool.h>

static void chip8_screen_is_bounds(int x, int y) {
  assert(x >= 0 && x < CHIP8_SCREEN_WIDTH && y >= 0 && y < CHIP8_SCREEN_HEIGHT);
}

void chip8_screen_clear(chip8_screen *screen) {
  memset(screen->pixels, 0, sizeof(screen->pixels));
}

void chip8_screen_set(chip8_screen *screen, int x, int y) {
  chip8_screen_is_bounds(x, y);
  screen->pixels[y][x] = true;
}

bool chip8_screen_is_set(chip8_screen *screen, int x, int y) {
  chip8_screen_is_bounds(x, y);
  return screen->pixels[y][x];
}

bool chip8_screen_draw_sprite(chip8_screen *screen, int x, int y,
                              const char *sprite, int num) {
  bool pixel_collision = false;

  for (int ly = 0; ly < num; ly++) {
    char c = sprite[ly];

    for (int lx = 0; lx < 8; lx++) {
      if ((c & (0b10000000 >> lx)) == 0) {
        continue;
      }

      if (screen->pixels[(ly + y) % CHIP8_SCREEN_HEIGHT]
                        [(lx + x) % CHIP8_SCREEN_WIDTH]) {
        pixel_collision = true;
      }

      screen->pixels[(ly + y) % CHIP8_SCREEN_HEIGHT]
                    [(lx + x) % CHIP8_SCREEN_WIDTH] ^= true;
    }
  }

  return pixel_collision;
}
