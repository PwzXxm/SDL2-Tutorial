#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

const int WIDTH = 1024;
const int HEIGHT = 768;

SDL_Window *window = NULL;

SDL_Texture *texture = NULL;
SDL_Renderer *renderer = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL2 Lesson 07 Texture Loading and Rendering",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WIDTH,
                              HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Failed to create renderer " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int img_flags = IMG_INIT_PNG;

    if ((IMG_Init(img_flags) & img_flags) != img_flags) {
        std::cerr << "SDL image could not initialize: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Texture *load_texture(std::string path) {
    SDL_Texture *new_texture = NULL;

    // load texture
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (surface == NULL) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    } else {
        new_texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (new_texture == NULL) {
            std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(surface);
    }

    return new_texture;
}

bool load_media() {
    texture = load_texture("../img/up.png");
    if (texture == NULL) {
        std::cerr << "Failed to load media" << std::endl;
        return false;
    }
    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyTexture(texture);
    texture = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
    if (!init()) {
        std::cerr << "Failed to initialize" << std::endl;
        return -1;
    }

    if (!load_media()) {
        std::cerr << "Failed to load media" << std::endl;
        return -1;
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    bool loop = true;
    while (loop) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
            }
        }
    }

    return 0;
}