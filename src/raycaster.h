#pragma once

#include <iostream>
#include <fstream>
#include <SDL_render.h>
#include <string>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <unordered_map>
#include "color.h"


const Color B = {0, 0, 0};
const Color W = {255, 255, 255};

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const int BLOCK = 50;


struct Player {
  int x;
  int y;
  float a;
  float fov;
}; 

std::unordered_map<std::string, Color> colors = {
  { "0", { 3, 150, 208 } },
  { "1", { 240, 200, 0 } },
  { "2", { 220, 36, 33 } },
  { "3", { 64, 169, 68 } }
};

struct Impact {
  float d;
  Color c;
};

class Raycaster {
public:
  Raycaster(SDL_Renderer* renderer)
    : renderer(renderer) {

    player.x = BLOCK + BLOCK / 2;
    player.y = BLOCK + BLOCK / 2;

    player.a = M_PI / 4.0f;
    player.fov = M_PI;

    scale = 100;
  }

  void load_map(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
      map.push_back(line);
    }
    file.close();
  }

  void point(int x, int y, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
  }

  void rect(int x, int y, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
    SDL_Rect rect = { x, y, BLOCK, BLOCK };
    SDL_RenderFillRect(renderer, &rect);
  }

  Impact cast_ray(float a) {
    float d = 0;
    std::string mapHit;
    while(true) {
      int x = static_cast<int>(player.x + d * cos(a)); 
      int y = static_cast<int>(player.y + d * sin(a)); 
      
      int i = static_cast<int>(x / BLOCK);
      int j = static_cast<int>(y / BLOCK);


      if (map[j][i] != ' ') {
        mapHit = map[j][i];
        break;
      }
     
      point(x, y, W);
      
      d += 1;
    }
    return Impact{d, colors[mapHit]};
  }

  void draw_stake(int x, float h, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
    float start = SCREEN_HEIGHT/2.0f - h/2.0f;
    SDL_Rect rect = { x, static_cast<int>(start), 1, static_cast<int>(h) };
    SDL_RenderFillRect(renderer, &rect);
  } 
 
  void render() {
    
    // draw left side of the screen
    
    for (int x = 0; x < SCREEN_WIDTH; x += BLOCK) {
      for (int y = 0; y < SCREEN_HEIGHT; y += BLOCK) {
        int i = static_cast<int>(x / BLOCK);
        int j = static_cast<int>(y / BLOCK);
        
        if (map[j][i] != ' ') {
          std::string mapHit;
          mapHit = map[j][i];
          Color c = colors[mapHit];
          rect(x, y, c);
        }
      }
    }

    for (int i = 1; i < SCREEN_WIDTH; i++) {
      float a = player.a + player.fov / 2 - player.fov * i / SCREEN_WIDTH;
      cast_ray(a);
    }

    // draw right side of the screen
    
    for (int i = 1; i < SCREEN_WIDTH; i++) {
      double a = player.a + player.fov / 2.0 - player.fov * i / SCREEN_WIDTH;
      Impact impact = cast_ray(a);
      float d = impact.d;
      Color c = impact.c;

      
      int x = SCREEN_WIDTH + i;
      float h = static_cast<float>(SCREEN_HEIGHT)/static_cast<float>(d) * static_cast<float>(scale);
      draw_stake(x, h, c);
    }

  }

  Player player;
private:
  int scale;
  SDL_Renderer* renderer;
  std::vector<std::string> map;
};