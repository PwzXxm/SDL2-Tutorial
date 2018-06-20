#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

const int WIDTH = 1024;
const int HEIGHT = 768;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

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

    int img_flags = IMG_INIT_PNG;
    if ((IMG_Init(img_flags) & img_flags) != img_flags) {
        std::cerr << "Failed to init Image subsytem: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Texture *load_texture(std::string path) {
    SDL_Texture *load_texture = NULL;
    SDL_Surface *load_surface = IMG_Load(path.c_str());
    if (load_surface == NULL) {
        std::cerr << "Failed to load surface: " << SDL_GetError() << std::endl;
    } else {
        load_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
        if (load_texture == NULL) {
            std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(load_surface);
    }
    return load_texture;
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
    SDL_DestroyTexture(texture);
    texture = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
    if (!init()) {
        std::cerr << "Failed to init" << std::endl;
        return -1;
    }

    if (!load_media()) {
        std::cerr << "Failed to load media" << std::endl;
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

        // viewport
        SDL_Rect top_left_viewport = {0, 0, WIDTH / 2, HEIGHT / 2};
        SDL_RenderSetViewport(renderer, &top_left_viewport);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_Rect top_right_viewport = {WIDTH / 2, 0, WIDTH / 2, HEIGHT / 2};
        SDL_RenderSetViewport(renderer, &top_right_viewport);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_Rect bot_viewport = {0, HEIGHT / 2, WIDTH, HEIGHT / 2};
        SDL_RenderSetViewport(renderer, &bot_viewport);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    close();

    return 0;
}