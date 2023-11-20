#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <thread>
#include <string>

#include "color.h"
#include "raycaster.h"
#include "imageloader.h"

SDL_Window* window;
SDL_Renderer* renderer;

int frames = 0;
Uint32 initialFrames;
Uint32 capTimer = 0;
const int SCREEN_FPS = 144;  
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int PlayMusic() {
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;

    if (SDL_LoadWAV("../assets/audios/gameAnthem.wav", &wavSpec, &wavBuffer, &wavLength) == nullptr) {
        return 1;
    }

    if (SDL_OpenAudio(&wavSpec, nullptr) < 0) {
        return 1;
    }

    while (true) {
        SDL_QueueAudio(1, wavBuffer, wavLength);
        SDL_PauseAudio(0);

        SDL_Delay(wavLength * 1000 / wavSpec.freq);

        SDL_QueueAudio(1, wavBuffer, wavLength);
        SDL_PauseAudio(0);
    }

    SDL_CloseAudio();
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();

    return 0;
}

int flashlightSound(){
  SDL_AudioSpec wavSpec;
  Uint32 wavLength;
  Uint8* wavBuffer;

  if (SDL_LoadWAV("../assets/audios/flashlight.wav", &wavSpec, &wavBuffer, &wavLength) == nullptr) {
      return 1;
  }

  SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);

  if (deviceId == 0) {
      return 1;
  }

  SDL_QueueAudio(deviceId, wavBuffer, wavLength);
  SDL_PauseAudioDevice(deviceId, 0);

  SDL_Delay(wavLength * 1000 / wavSpec.freq);

  SDL_CloseAudioDevice(deviceId);
  SDL_FreeWAV(wavBuffer);

  return 0;
}

void playFlashlightSound(){
  flashlightSound();
}

void clear() {
  SDL_SetRenderDrawColor(renderer, B.r, B.g, B.b, 0);
  SDL_RenderClear(renderer);
}

void draw_floor(Raycaster& r) {
  // floor color
  SDL_SetRenderDrawColor(renderer, 56 * r.view, 56 * r.view, 56 * r.view, 255);
  SDL_Rect rect = {
    SCREEN_WIDTH / 2 - BLOCK * 2 * r.view, 
    SCREEN_HEIGHT / 2,
    BLOCK * r.view * 4,
    SCREEN_HEIGHT * r.view / 4
  };
  SDL_RenderFillRect(renderer, &rect);
}

void draw_ui(std::string player){
  int size = 128;
  ImageLoader::render(renderer, player, SCREEN_WIDTH / 2.0f - size / 2.0f, SCREEN_HEIGHT - size, size);
}

void startingScreen(){
  SDL_Surface* surface = IMG_Load("../assets/screens/startingScreen.jpeg");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_Delay(3000);
}

std::string levelScreen(){
  SDL_Surface* surface = IMG_Load("../assets/screens/levelScreen.png");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  SDL_Event event;
  while (true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_KEYDOWN) {
      switch(event.key.keysym.sym ){
        case SDLK_a:
          return "../assets/maps/levelA.txt";
          break;
        case SDLK_b:
          return "../assets/maps/levelB.txt";
          break;
        default:
          break;
      }
    }
  }
}

void endingScreen(){
  SDL_Surface* surface = IMG_Load("../assets/screens/endingScreen.jpeg");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_Delay(3000);

  SDL_DestroyWindow(window);
}

int main(int argv, char** args) {
  SDL_Init(SDL_INIT_VIDEO);

  ImageLoader::init();

  window = SDL_CreateWindow("DOOM", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  ImageLoader::loadImage("+", "../assets/textures/wall3.png");
  ImageLoader::loadImage("-", "../assets/textures/wall2.png");
  ImageLoader::loadImage("|", "../assets/textures/wall1.png");
  ImageLoader::loadImage("p", "../assets/textures/player.png");
  ImageLoader::loadImage("f", "../assets/textures/flashlight.png");
  ImageLoader::loadImage("*", "../assets/textures/door.jpeg");

  std::string player = "p";

  Raycaster r = { renderer };

  bool running = true;
  int speed = 10;
  
  std::thread music(PlayMusic);

  startingScreen();
  std::string level = levelScreen();
  r.load_map(level);

  bool win = false;
  
  while(running) {
    SDL_Event event;
    initialFrames = SDL_GetTicks();


    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT || win) {
        running = false;
        break;
      }

      if (player == "f"){
        r.view = 1;
      }
      else if (player == "p"){
        r.view = 2;
      }

      if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym ){
          case SDLK_LEFT: {
            if (player == "f"){
              break;
            }
            r.player.a += 3.14/24;
            if (r.player.a > 2 * M_PI) {
                r.player.a -= 2 * M_PI;
            }
          }
            break;
          case SDLK_RIGHT: {
            if (player == "f"){
              break;
            }
            r.player.a -= 3.14/24;
            if (r.player.a > 2 * M_PI) {
                r.player.a -= 2 * M_PI;
            }
          }
            break;
          case SDLK_UP: {
            if (player == "f"){
              break;
            }

            int nextx = r.player.x + speed * cos(r.player.a);
            int nexty = r.player.y + speed * sin(r.player.a);

            if (r.map[nexty / BLOCK][nextx / BLOCK] == ' ') {
              r.player.x += speed * cos(r.player.a);
              r.player.y += speed * sin(r.player.a);
            }

            if (r.map[nexty / BLOCK][nextx / BLOCK] == '*') {
              endingScreen();
              win = true;
              break;
            }
          }
            break;
          case SDLK_DOWN: {
            if (player == "f"){
              break;
            }

            int nextx = r.player.x - speed * cos(r.player.a);
            int nexty = r.player.y - speed * sin(r.player.a);

            if (r.map[nexty / BLOCK][nextx / BLOCK] == ' ') {
              r.player.x -= speed * cos(r.player.a);
              r.player.y -= speed * sin(r.player.a);
            }
          }
            break;

          case SDLK_SPACE:{
            std::thread flashlight(playFlashlightSound);
            flashlight.detach();
            if (player == "p"){
              player = "f";
            }else{
              player = "p";
            }
          }
            break;
           default:
            break;
        }
      }

      if (event.type == SDL_MOUSEMOTION && player == "p") {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        static int prevMouseX = mouseX;
        int mouseDeltaX = mouseX - prevMouseX;

        r.player.a -= static_cast<float>(mouseDeltaX) * 0.005f;

        if (r.player.a > 2 * M_PI) {
            r.player.a -= 2 * M_PI;
        } else if (r.player.a < 0) {
            r.player.a += 2 * M_PI;
        }

        prevMouseX = mouseX;
    }

    }

    clear();
    draw_floor(r);

    r.render();

    draw_ui(player);

    SDL_RenderPresent(renderer);

    ++frames;
    int frameTicks = SDL_GetTicks() - initialFrames;
    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }

    if (SDL_GetTicks() - capTimer >= 1000) {
        capTimer = SDL_GetTicks();
        std::string windowTitle = "DOOM | FPS: " + std::to_string(frames);
        SDL_SetWindowTitle(window, windowTitle.c_str());
        frames = 0;
    }
  }

  music.join();

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}