#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "MyTexture.h"

const int kWidth = 1024;
const int kHeight = 768;

const int kWalkingAnimationFrames = 4;
const int kClips[kWalkingAnimationFrames][4] = {0, 0, 64, 205, 64, 0, 64, 205, 128, 0, 64, 205, 196, 0, 64, 205};
MyTexture sprite_sheet_texture;
SDL_Rect spirte_clips[kWalkingAnimationFrames];

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool LoadMedia() {
    if (!sprite_sheet_texture.Load(renderer, "../img/foo_copyright_reserved_by_lazy_foo.png")) {
        std::cerr << "Failed to load sprite" << std::endl;
        return false;
    }

    for (int i = 0; i < kWalkingAnimationFrames; i++) {
        int j = 0;
        spirte_clips[i].x = kClips[i][j++];
        spirte_clips[i].y = kClips[i][j++];
        spirte_clips[i].w = kClips[i][j++];
        spirte_clips[i].h = kClips[i][j++];
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
    sprite_sheet_texture.Free();

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

    // current frame
    int frame = 0;

    while (loop) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        // clip sprite
        SDL_Rect *current_clip = &spirte_clips[frame / 4];
        sprite_sheet_texture.Render(renderer, (kWidth - current_clip->w) / 2, (kHeight - current_clip->h) / 2, current_clip);

        SDL_RenderPresent(renderer);

        // update frame
        ++frame;

        if (frame / 4 >= kWalkingAnimationFrames) {
            frame = 0;
        }
    }

    Close();

    return 0;
}