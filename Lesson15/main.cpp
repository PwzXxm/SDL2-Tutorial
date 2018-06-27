#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "MyTexture.h"

const int kWidth = 1024;
const int kHeight = 768;

MyTexture sprite_rotate_texture;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool LoadMedia() {
    if (!sprite_rotate_texture.Load(renderer, "../img/arrow_rotation_lazy_foo.png")) {
        std::cerr << "Failed to load sprite" << std::endl;
        return false;
    }

    return true;
}

bool Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to init video: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "Lesson 13 Alpha Blending", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kWidth, kHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    int img_flag = IMG_INIT_PNG;
    if ((IMG_Init(img_flag) & img_flag) != img_flag) {
        std::cerr << "Failed to init img: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

void Close() {
    sprite_rotate_texture.Free();

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
    if (!Init()) {
        std::cerr << "Failed to init" << std::endl;
        return -1;
    }

    if (!LoadMedia()) {
        std::cerr << "Failed to load media" << std::endl;
        return -1;
    }

    bool loop = true;
    SDL_Event e;

    // rotation angle
    double degrees = 0;
    // flip type
    SDL_RendererFlip flip_type = SDL_FLIP_NONE;

    while (loop) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        degrees -= 60;
                        break;
                    case SDLK_RIGHT:
                        degrees += 60;
                        break;
                    case SDLK_UP:
                        flip_type = SDL_FLIP_HORIZONTAL;
                        break;
                    case SDLK_DOWN:
                        flip_type = SDL_FLIP_VERTICAL;
                        break;
                    default:
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        // render
        sprite_rotate_texture.Render(renderer,
                                     (kWidth - sprite_rotate_texture.GetWidth()) / 2,
                                     (kHeight - sprite_rotate_texture.GetHeight()) / 2,
                                     NULL,
                                     degrees,
                                     NULL,
                                     flip_type);

        SDL_RenderPresent(renderer);
    }

    Close();

    return 0;
}