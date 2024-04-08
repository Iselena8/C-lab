#ifndef INIT_RENDER_H
#define INIT_RENDER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "block.h"

const int SCREEN_WIDTH = 510;
const int SCREEN_HEIGHT = 860;

bool init(); // 初始化SDL并创建窗口
bool loadMedia(SDL_Texture **texture, SDL_Renderer *renderer, std::string &path, Shape *currentBlock);
void close(SDL_Texture *texture, SDL_Texture *backgroundTexture, SDL_Renderer *renderer, SDL_Window *window); // 释放资源

SDL_Renderer *renderer = nullptr; // 渲染器
SDL_Window *window = nullptr;     // 要渲染的窗口

const int FPS = 1;      // 目标帧率
const int QUICKFPS = 2; // 加速帧率

const int GRID_ROWS = 20;
const int GRID_COLS = 12;

std::vector<std::vector<backgroundcell>> grid; // 创建一个二维数组储存坐标

bool init()
{
    bool success = true; // 初始化标记变量

    if (SDL_Init(SDL_INIT_VIDEO) < 0) // 初始化SDL
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr)
            {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
        }
    }

    // 给背景图中的每一个格子设置坐标
    grid.resize(GRID_ROWS, std::vector<backgroundcell>(GRID_COLS));
    for (int row = 0; row < GRID_ROWS; ++row)
    {
        for (int col = 0; col < GRID_COLS; ++col)
        {
            grid[row][col] = backgroundcell(row, col);
        }
    }

    return success;
}

bool loadMedia(SDL_Texture **texture, SDL_Renderer *renderer, std::string &path, Shape *currentBlock)
{
    bool success = true; // 初始化标记变量

    // 生成一个随机数，范围在 0 到 8 之间
    int randomSurfaceIndex = rand() % 7;

    // 图形名称
    std::string shapeName;

    if (dynamic_cast<rectangle *>(currentBlock))
    {
        shapeName = "rectangle";
    }
    else if (dynamic_cast<leftL *>(currentBlock))
    {
        shapeName = "leftL";
    }
    else if (dynamic_cast<rightL *>(currentBlock))
    {
        shapeName = "rightL";
    }
    else if (dynamic_cast<square *>(currentBlock))
    {
        shapeName = "square";
    }
    else if (dynamic_cast<leftZ *>(currentBlock))
    {
        shapeName = "leftZ";
    }
    else if (dynamic_cast<rightZ *>(currentBlock))
    {
        shapeName = "rightZ";
    }
    else if (dynamic_cast<ding *>(currentBlock))
    {
        shapeName = "ding";
    }
    path="picture/"+shapeName+std::to_string(currentBlock->rotation)+".bmp";

    // 根据随机数选择要加载的图片路径
    switch (randomSurfaceIndex)
    {
    case 0:
        path = "picture/方块1.bmp";
        break;
    case 1:
        path = "picture/长条1.bmp";
        break;
    case 2:
        path = "picture/左Z1.bmp";
        break;
    case 3:
        path = "picture/右Z1.bmp";
        break;
    case 4:
        path = "picture/左L1.bmp";
        break;
    case 5:
        path = "picture/右L1.bmp";
        break;
    case 6:
        path = "picture/丁字1.bmp";
        break;
    }

    // 载入图像
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());

    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image " << path << "! SDL_image Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        *texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (*texture == nullptr)
        {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }

        SDL_FreeSurface(loadedSurface);
    }

    return success;
}

void close(SDL_Texture *texture, SDL_Texture *backgroundTexture, SDL_Renderer *renderer, SDL_Window *window)
{
    // 释放图像
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(backgroundTexture);

    // 释放窗口
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;
    backgroundTexture = nullptr;
    texture = nullptr;

    // 退出SDL
    SDL_Quit();
}

#endif