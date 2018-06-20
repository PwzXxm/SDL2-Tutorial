#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

const int WIDTH = 1024;
const int HEIGHT = 768;

SDL_Window *window = NULL;
SDL_Surface *screen_surface = NULL;
SDL_Surface *cur_surface = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialiazation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow("SDL Lesson 06 Extension Libraries and Loading Other Image Formats",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WIDTH,
                              HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize PNG loading
    int img_flag = IMG_INIT_PNG;
    if (!(IMG_Init(img_flag) & img_flag)) {
        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
    }

    screen_surface = SDL_GetWindowSurface(window);

    return true;
}

SDL_Surface *loadSurface(std::string path) {
    SDL_Surface *opt_surface = NULL;
    // load image
    SDL_Surface *load_surface = IMG_Load(path.c_str());
    if (load_surface == NULL) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    } else {
        opt_surface = SDL_ConvertSurface(load_surface, screen_surface->format, NULL);
        if (opt_surface == NULL) {
            std::cerr << "Failed to optimize image: " << SDL_GetError << std::endl;
        }
        SDL_FreeSurface(load_surface);
    }
    return opt_surface;
}

void close() {
    SDL_FreeSurface(cur_surface);
    cur_surface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (!init()) {
        std::cerr << "Initialization failed" << std::endl;
        return -1;
    }

    cur_surface = loadSurface("../img/up.png");
    if (cur_surface == NULL) {
        std::cerr << "Failed to load surface" << std::endl;
        return -1;
    }

    SDL_BlitSurface(cur_surface, NULL, screen_surface, NULL);
    SDL_UpdateWindowSurface(window);

    bool loop = true;
    while (loop) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
            }
        }
    }

    close();

    return 0;
}