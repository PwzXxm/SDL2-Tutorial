#include <SDL2/SDL.h>
#include <iostream>

const int WIDTH = 1024;
const int HEIGHT = 768;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to init: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "SDL2 Lesson 08 Geometry Rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    if (SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff) < 0) {
        std::cerr << "Failed to set renderer drawing color: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

int main(int argc, char *args[]) {
    if (!init()) {
        std::cerr << "Failed to init" << std::endl;
        return -1;
    }

    bool loop = true;
    while (loop) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
            }
        }

        // clear
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        // red rect
        SDL_Rect fill_rect = {WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2};
        SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
        SDL_RenderFillRect(renderer, &fill_rect);

        // green rect
        SDL_Rect out_rect = {WIDTH / 6, HEIGHT / 6, WIDTH * 2 / 3, HEIGHT * 2 / 3};
        SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
        SDL_RenderDrawRect(renderer, &out_rect);

        // blue horizontal line
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
        SDL_RenderDrawLine(renderer, 0, HEIGHT / 2, WIDTH, HEIGHT / 2);

        // vertical dotted line
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff);
        for (int i = 0; i < HEIGHT; i += 4) {
            SDL_RenderDrawPoint(renderer, WIDTH / 2, i);
        }

        SDL_RenderPresent(renderer);
    }

    close();

    return 0;
}