#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <vector>
#include "Box/box.h"

SDL_Window *window = SDL_CreateWindow("2D 物理沙盒 程序窗口", 1280, 1000, 0);
SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

/// <summary>
/// 主循环
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void MainLoop()
{
    /* 事件循环 */
    bool isQuit = false;
    SDL_Event event;

    glm::vec2 mousePos = glm::vec2(0.0f, 0.0f);
    std::vector<Box> vecBox;

    while (!isQuit)
    {
        // 1. 处理输入 (Input)
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                isQuit = true;
            }

            //// 点击一次执行一次
            // 只有在按下的一瞬间（Down）才执行逻辑
            // if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            // {
            //     // 检查是不是左键
            //     if (event.button.button == SDL_BUTTON_LEFT)
            //     {
            //         Box b = CreateBox(event.button.x, event.button.y);
            //         vecBox.push_back(b);
            //     }
            // }
        }

        //// 点击不放一直执行
        auto state = SDL_GetMouseState(&mousePos.x, &mousePos.y);
        if (state & SDL_BUTTON_LMASK)
        {
            Box b = CreateBox(mousePos.x, mousePos.y);
            vecBox.push_back(b);
        }

        SDL_Log("vecBox count : %d", vecBox.size());

        // 渲染画面 (Render)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 背景黑
        SDL_RenderClear(renderer);

        for (int i = 0; i < vecBox.size(); i++)
        {
            // 物理更新 (Update)
            UpdateBox(vecBox[i]);

            // 绘制沙盒物体
            RenderBox(renderer, vecBox[i]);
        }

        SDL_RenderPresent(renderer);

        // 控制帧率
        SDL_Delay(16); // 粗略锁定约 60FPS
    }
}

/// <summary>
/// 主函数
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int main(int argc, char *argv[])
{
    /* 初始化 SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL 初始化失败: %s\n", SDL_GetError());
        return -1;
    }

    /* 创建窗口 */
    if (!window)
    {
        printf("窗口创建失败: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    /* 创建渲染器 */
    if (!renderer)
    {
        printf("渲染器创建失败: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    MainLoop();

    /* 清理与退出 */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
