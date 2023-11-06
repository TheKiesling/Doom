#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include "color.h"
#include "raycaster.h"

SDL_Window* window;
SDL_Renderer* renderer;

void clear() {
  SDL_SetRenderDrawColor(renderer, B.r, B.g, B.b, 0);
  SDL_RenderClear(renderer);
}

int main(int argv, char** args) {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("DOOM", 0, 0, 2000, 1000, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  Raycaster r = { renderer };
  r.load_map("../assets/map.txt");

  bool running = true;
  while(running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }
      if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym ){
          case SDLK_LEFT:
            r.player.x -= 10;
            break;
          case SDLK_RIGHT:
            r.player.x += 10;
            break;
          case SDLK_UP:
            r.player.y -= 10;
            break;
          case SDLK_DOWN:
            r.player.y += 10;
            break;
          case SDLK_a:
            r.player.a += 3.14/12;
            break;
          case SDLK_d:
            r.player.a -= 3.14/12;
            break;
           default:
            break;
        }
      }
    }

    clear();

    r.render();

    // render

    SDL_RenderPresent(renderer);
  }
  

  return 0;
}