#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <SDL3/SDL_render.h>
#include "../Constant/constant.h"

/// <summary>
/// 方块类
/// </summary>
/// <param name=""></param>
/// <returns></returns>
class Box
{
  public:
    float x;
    float y;
    float w;
    float h;
    float velocity;
    SDL_Color color;

  public:
    Box(float x, float y, float w, float h, float v, SDL_Color c);
};

void UpdateBox(Box &box, float gravity);

void RenderBox(SDL_Renderer *renderer, Box &box);

Box CreateBox(float x, float y, SDL_Color color);
