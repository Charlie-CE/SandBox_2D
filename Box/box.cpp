#include "box.h"

/// <summary>
/// 构造函数 Box
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="v"></param>
/// <param name="g"></param>
/// <param name="c"></param>
/// <returns></returns>
Box::Box(float x, float y, float w, float h, float v, float g, SDL_Color c)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->velocity = v;
    this->gravity = g;
    this->color = c;
}

/// <summary>
/// 更新Box
/// </summary>
/// <param name="Pos"></param>
/// <returns></returns>
void UpdateBox(Box &box)
{
    // 物理更新 (Update)
    // 这里是物理引擎（如 Box2D）计算位移的地方
    box.velocity += box.gravity * 0.016f; // 简单模拟
    box.y += box.velocity;
}

/// <summary>
/// 绘制Box
/// </summary>
/// <param name="renderer"></param>
/// <returns></returns>
void RenderBox(SDL_Renderer *renderer, Box &box)
{
    SDL_FRect rect = {box.x, box.y, box.w, box.h};
    SDL_SetRenderDrawColor(renderer, box.color.r, box.color.g, box.color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

/// <summary>
/// 创造一个方块
/// </summary>
/// <returns>Box</returns>
Box CreateBox(float x, float y)
{
    std::srand(std::time(NULL));

    /* --- 初始化Box数据 --- */
    float w = 40.f;
    float h = 40.f;
    float v = 0.0f;
    float g = 9.8f;
    Uint8 color_r = std::rand() % 256;
    Uint8 color_g = std::rand() % 256;
    Uint8 color_b = std::rand() % 256;
    SDL_Color *c = new SDL_Color({color_r, color_g, color_b});

    Box *box = new Box(x, y, w, h, v, g, *c);

    return *box;
}
