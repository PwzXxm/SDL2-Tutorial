#include <SDL2/SDL.h>
#include <iostream>
#include <string>

const int WIDTH = 1024;
const int HEIGHT = 768;

SDL_Window *window = NULL;
SDL_Surface *default_surf = NULL;
SDL_Surface *cur_surf = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Init SDL failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL Lesson 05 Optimized Surface Loading and Soft Stretching",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WIDTH,
                              HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cerr << "Init window failed: " << SDL_GetError() << std::endl;
        return false;
    }

    default_surf = SDL_GetWindowSurface(window);

    return true;
}

SDL_Surface *load_surface(std::string path) {
    SDL_Surface *opt_surf = NULL;
    SDL_Surface *load_surf = SDL_LoadBMP(path.c_str());
    if (load_surf == NULL) {
        std::cerr << "Failed to load BMP image: " << SDL_GetError() << std::endl;
    } else {
        // convert to screen bitmap format
        opt_surf = SDL_ConvertSurface(load_surf, default_surf->format, NULL);
        if (opt_surf == NULL) {
            std::cerr << "Failed to optimize image: " << SDL_GetError() << std::endl;
            return load_surf;
        }
        SDL_FreeSurface(load_surf);
    }
    return opt_surf;
}

void close() {
    SDL_FreeSurface(cur_surf);
    cur_surf = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (!init()) {
        std::cerr << "Failed to init" << std::endl;
        return -1;
    }

    cur_surf = load_surface("../img/star.bmp");
    if (cur_surf == NULL) {
        std::cerr << "Failed to load surface" << std::endl;
        return -1;
    }
    // stretch surface
    SDL_Rect stretch_rect;
    stretch_rect.x = 0;
    stretch_rect.y = 0;
    stretch_rect.w = WIDTH;
    stretch_rect.h = HEIGHT;
    SDL_BlitScaled(cur_surf, NULL, default_surf, &stretch_rect);
    SDL_UpdateWindowSurface(window);

    bool loop = true;
    SDL_Event e;

    while (loop) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
            }
        }
    }

    close();

    return 0;
}