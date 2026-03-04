#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include "Box/box.h"
#include "Constant/constant.h"
#include "SDL3/SDL_pixels.h"

SDL_Window *window = SDL_CreateWindow("2D 物理沙盒 程序窗口", Window_Wdith, Window_Height, 0);
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
    glm::vec2 boxSize(10.0f, 10.0f);

    std::vector<Box> vecBox;

    float boxMass = 1.0f;
    float gGravity = 9.8f;

    SDL_Color gColor = {255, 255, 0, 255}; // 黄色

    // 初始化时间
    Uint32 last_time = SDL_GetTicks();

    while (!isQuit)
    {
        // 处理输入 (Input)
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                // 退出程序
            case SDL_EVENT_QUIT:
                isQuit = true;
                break;

            // 键盘按下事件
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key)
                {
                case SDLK_C:
                    vecBox.clear(); // 清空所有方块
                    SDL_Log("已执行清空 (C Key Pressed)");
                    break;

                case SDLK_ESCAPE:
                    isQuit = true; // 按下 ESC 退出程序
                    break;
                default:
                    break;
                }
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                // 检查是不是左键
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mousePos.x, &mousePos.y);
                    // 调用工厂函数并存入 vector
                    vecBox.push_back(CreateBox(mousePos, boxSize, boxMass, gColor));
                }
                SDL_Log("vecBox %d", vecBox.size());
                break;
            default:
                break;
            }
        }

        //// 点击不放一直执行
        // auto state = SDL_GetMouseState(&mousePos.x, &mousePos.y);
        // if (state & SDL_BUTTON_LMASK)
        // {
        //     gColor = new SDL_Color({(uint8_t)(std::rand() % 256), (uint8_t)(std::rand() % 256), (uint8_t)(std::rand() % 256)});
        //     vecBox.push_back(CreateBox(mousePos, boxSize, boxMass, gColor));
        // }

        // gColor = {(uint8_t)(std::rand() % 256), (uint8_t)(std::rand() % 256), 0, 255};

        // 渲染画面 (Render)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 背景黑
        SDL_RenderClear(renderer);

        // 獲取當前時間
        Uint32 current_time = SDL_GetTicks();

        for (int i = 0; i < vecBox.size(); i++)
        {
            // 物理更新 (Update)
            float dt = (current_time - last_time) / 1000.0f;
            vecBox[i].UpdateBox(dt, gGravity);

            // 绘制沙盒物体
            vecBox[i].RenderBox(renderer);
        }

        SDL_RenderPresent(renderer);

        // 控制帧率
        SDL_Delay(16); // 粗略锁定约 60FPS
        last_time = current_time;
    }
}

/// <summary>
/// 主函数
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int main(int argc, char *argv[])
{
    std::srand(std::time(NULL));

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
