#include "box.h"

/// <summary>
/// 更新Box
/// </summary>
/// <param name="dt"></param>
/// <returns></returns>
void Box::UpdateBox(float dt, float gravity)
{
    // 质量超重的石头 -> 不会移动
    if (inv_mass == 0)
    {
        return;
    }

    // 重力只影响 Y 轴
    velocity.y += 9.8f * 100.0f * dt; // 这里的 100.0 是像素/米 的比例转换

    // 更新位置
    position += velocity * dt;

    // 底部碰撞 (Y 轴反弹)
    if (position.y + size.y >= (float)Window_Height)
    {
        position.y = (float)Window_Height - size.y;
        velocity.y = -velocity.y * restitution;

        // 落地时，水平方向因为摩擦力而减速
        velocity.x *= (1.0f - friction);
    }

    // 左右墙壁碰撞 (X 轴反弹)
    if (position.x <= 0 || position.x + size.x >= (float)Window_Height)
    {
        velocity.x = -velocity.x * restitution;
        // 修正位置防止穿墙
        position.x = (position.x <= 0) ? 0 : (float)Window_Height - size.x;
    }
}

/// <summary>
/// 绘制Box
/// </summary>
/// <param name="renderer"></param>
/// <returns></returns>
void Box::RenderBox(SDL_Renderer *renderer)
{
    SDL_FRect rect = {position.x, position.y, size.x, size.y};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

/// <summary>
/// 创造一个方块
/// </summary>
/// <param name="pos"></param>
/// <param name="size"></param>
/// <param name="mass"></param>
/// <param name="color"></param>
/// <returns>Box</returns>
Box CreateBox(glm::vec2 pos, glm::vec2 size, float mass, SDL_Color color)
{
    // 1. 逻辑计算：在这里可以做一些初始化的随机化
    // 比如：给方块一个随机的初始水平速度，让它看起来更像“喷”出来的
    float randomVX = (float)(SDL_rand(200) - 100); // -100 到 100 之间
    glm::vec2 initialVel = glm::vec2(randomVX, 0.0f);

    // 2. 直接构造对象并返回
    // 注意：inv_mass 等属性可以在 Box 的构造函数内部自动计算
    Box newBox(pos, size, mass, color);

    newBox.velocity = initialVel;
    newBox.restitution = 0.6f; // 给它 60% 的弹性
    newBox.friction = 0.2f;    // 给点摩擦力

    return newBox;
}
