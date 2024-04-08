#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "block.h"
#include "init.h"
#include "function.h"

/* SDL_Init(): 用于初始化SDL库。
SDL_CreateWindow(): 用于创建一个窗口,俄罗斯方块游戏在此窗口中渲染。
SDL_CreateRenderer(): 用于创建一个渲染器,用于在窗口上绘制图形。
SDL_RenderClear(): 用于清除渲染器上的当前绘制内容。
SDL_RenderCopy(): 用于将一个纹理复制到渲染器上。
SDL_RenderPresent(): 用于显示渲染器上绘制的图形。
SDL_PollEvent(): 用于获取并处理用户输入事件,如键盘和鼠标事件。
SDL_Delay(): 用于控制游戏循环的速度。
SDL_LoadBMP()/SDL_LoadTexture(): 用于加载游戏中使用的图像资源。
SDL_RenderCopy(): 用于绘制游戏元素(如方块、背景等)。
SDL_Quit(): 用于在程序退出时正确释放资源。*/

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));
    bool quit = false;

    SDL_Event e;

    if (!init())
    {
        std::cout << "Failed to initialize!" << std::endl;
        return 1;
    }
    else
    {
        SDL_Texture *backgroundTexture = nullptr;
        SDL_Texture *texture = nullptr;

        // 加载背景图片
        std::string backgroundPath = "picture/背景图.bmp";
        SDL_Surface *backgroundSurface = SDL_LoadBMP(backgroundPath.c_str());
        if (backgroundSurface == nullptr)
        {
            std::cout << "Unable to load background image! SDL Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
            if (backgroundTexture == nullptr)
            {
                std::cout << "Unable to create texture from background image! SDL Error: " << SDL_GetError() << std::endl;
            }
            SDL_FreeSurface(backgroundSurface);
        }

        std::unique_ptr<Shape> currentBlock = getRandomShape();
        SDL_Rect destRect = {212, 0, 0, 0}; // 设置目标矩形的左上角坐标为212，0
        int frameDelay = 1000 / FPS; //计算每帧的延迟时间

        while (!quit)
        {
            SDL_RenderClear(renderer);

            // 渲染背景
            if (backgroundTexture != nullptr)
            {
                SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
            }

            if (!currentBlock->drop)
            {
                SDL_DestroyTexture(texture);
                texture = nullptr;

                std::string path;
                if (loadMedia(&texture, renderer, path, currentBlock.get())) // 加载前景图片
                {
                    SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
                    SDL_RenderCopy(renderer, texture, nullptr, &destRect); // 渲染前景
                }
                else
                {
                    std::cout << "Failed to load media!" << std::endl;
                }
            }
            else
            {
                // 渲染当前方块
                SDL_RenderCopy(renderer, texture, nullptr, &destRect);
                // 更新方块位置坐标
                destRect.y += 42;

                if (destRect.y + destRect.h >= SCREEN_HEIGHT)
                {
                    currentBlock->drop = false;
                    destRect.y = 0;
                }

                //控制帧率
                int currentTicks = SDL_GetTicks();
                int elapsedTicks = currentTicks - SDL_GetTicks();

                if (elapsedTicks < frameDelay)
                {
                    SDL_Delay(frameDelay - elapsedTicks);
                }
            }

            SDL_RenderPresent(renderer);

            // 处理事件
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    handleInput(event, currentBlock);
                }
            }
        }

        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
        close(texture, nullptr, renderer, window);
    }

    return 0;
}