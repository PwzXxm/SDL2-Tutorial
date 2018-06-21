#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "MyTexture.h"

const int kWidth = 1024;
const int kHeight = 768;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Rect sprite_rect[4];
MyTexture alpha_texture, bg_texture;

bool LoadMedia() {
    if (!alpha_texture.Load(renderer, "../img/up.png")) {
        std::cerr << "Failed to load alpha" << std::endl;
        return false;
    }

    alpha_texture.SetBlendMode(SDL_BLENDMODE_BLEND);

    if (!bg_texture.Load(renderer, "../img/bg.png")) {
        std::cerr << "Failed to load bg" << std::endl;
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
    alpha_texture.Free();

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
    Uint8 alpha = 255;
    int offset = 15;

    while (loop) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        if (alpha + offset >= 255) {
                            alpha = 255;
                        } else {
                            alpha += offset;
                        }
                        break;
                    case SDLK_LEFT:
                        if (alpha - offset <= 0) {
                            alpha = 0;
                        } else {
                            alpha -= offset;
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        bg_texture.Render(renderer, 0, 0);
        alpha_texture.SetAlpha(alpha);
        alpha_texture.Render(renderer, 0, 0);

        SDL_RenderPresent(renderer);
    }

    Close();

    return 0;
}