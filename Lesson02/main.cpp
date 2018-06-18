#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

SDL_Window *window = NULL;
SDL_Surface *defaultSurface = NULL;
SDL_Surface *imgSurf = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL Lesson 02", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    defaultSurface = SDL_GetWindowSurface(window);

    return true;
}

bool loadMedia() {
    imgSurf = SDL_LoadBMP("../img/star.bmp");
    if (imgSurf == NULL) {
        std::cerr << "Unable to load BMP image: " << SDL_GetError()
                  << std::endl;
        return false;
    }
    return true;
}

void close() {
    SDL_FreeSurface(imgSurf);
    imgSurf = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

int main(int argc, char *args[]) {
    if (!init()) {
        std::cerr << "Initialization failed!" << std::endl;
        return -1;
    } else {
        // tod
    }
    if (!loadMedia()) {
        std::cerr << "Load media failed" << std::endl;
        return -1;
    }
    SDL_FillRect(defaultSurface, NULL,
                 SDL_MapRGB(defaultSurface->format, 255, 0, 0));

    SDL_BlitSurface(imgSurf, NULL, defaultSurface, NULL);
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