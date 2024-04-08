#ifndef FUNCTION_H
#define FUNCTION_H
#include <SDL2/SDL.h>
#include <memory>
#include "block.h"
void handleInput(SDL_Event &event, std::unique_ptr<Shape> &currentBlock);


void handleInput(SDL_Event &event, std::unique_ptr<Shape> &currentBlock)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_q:
            currentBlock->rotation = (currentBlock->rotation + 3) % 4;
            break;
        case SDLK_e:
            currentBlock->rotation = (currentBlock->rotation + 1) % 4;
            break;
        case SDLK_SPACE:
            currentBlock = getRandomShape();
            break;
        }
    }
}

#endif