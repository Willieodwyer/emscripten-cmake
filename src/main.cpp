#include <stdio.h>
#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "mandelbrot.h"

#include <vector>

SDL_Surface* screen = nullptr;

int counter = 0; // Start from 60 (actually generates something from there)

void drawFrame() 
{
  printf("Iterations: %d!\n", counter);

  SDL_LockSurface(screen);

  mandelbrot(counter, -0.7436447860, 0.1318252536, 0.00029336);
  counter += 10;

  unsigned char* image = getImage();

  for(int x = 0.0; x < WIDTH; x++) {
    for(int y = 0.0; y < HEIGHT; y++) {
      int idx = ((x + y * WIDTH) * 4);
      *((Uint32*)screen->pixels + x + (y * WIDTH)) 
      = SDL_MapRGBA(screen->format, image[idx], image[idx + 1], image[idx + 2], image[idx + 3]);
    }
  }

  SDL_UnlockSurface(screen);
  SDL_Flip(screen);
}

extern "C" int main(int argc, char** argv) {
  printf("hello, world!\n");

  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

  emscripten_set_main_loop(drawFrame, 0, 1);

  return 0;
}

