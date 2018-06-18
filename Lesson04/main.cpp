#include <SDL2/SDL.h>
#include <iostream>
#include <string>

// Keypress surfaces constants
enum KeyPressSurfaces {
    SURFACE_DEFAULT,
    SURFACE_UP,
    SURFACE_DOWN,
    SURFACE_LEFT,
    SURFACE_RIGHT,
    SURFACE_TOTAL
};

const int WIDTH = 1024;
const int HEIGHT = 768;

SDL_Window *window = NULL;
SDL_Surface *default_surf = NULL;
SDL_Surface *keypress_surf[SURFACE_TOTAL];
SDL_Surface *cur_surf = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Init SDL failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL Lesson 04 Key Presses",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cerr << "Init window failed: " << SDL_GetError() << std::endl;
        return false;
    }

    default_surf = SDL_GetWindowSurface(window);

    return true;
}

SDL_Surface *load_surface(std::string path) {
    SDL_Surface *surf = SDL_LoadBMP(path.c_str());
    if (surf == NULL) {
        std::cerr << "Failed to load BMP image: " << SDL_GetError()
                  << std::endl;
    }
    return surf;
}

bool load_media() {
    for (int i = 0; i < SURFACE_TOTAL; i++) {
        keypress_surf[i] =
            load_surface("../img/keypress/" + std::to_string(i) + ".bmp");
        if (keypress_surf[i] == NULL) {
            std::cerr << "Failed to load image " << std::to_string(i)
                      << std::endl;
            return false;
        }
    }
    return true;
}

void close() {
    for (int i = 0; i < SURFACE_TOTAL; i++) {
        SDL_FreeSurface(keypress_surf[i]);
        keypress_surf[i] = NULL;
    }

    cur_surf = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (!init()) {
        std::cerr << "Failed to init" << std::endl;
        return -1;
    }

    if (!load_media()) {
        std::cerr << "Failed to load media" << std::endl;
    }

    bool loop = true;
    SDL_Event e;
    cur_surf = keypress_surf[SURFACE_DEFAULT];

    while (loop) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
            } else if (e.type = SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        cur_surf = keypress_surf[SURFACE_UP];
                        break;
                    case SDLK_DOWN:
                        cur_surf = keypress_surf[SURFACE_DOWN];
                        break;
                    case SDLK_LEFT:
                        cur_surf = keypress_surf[SURFACE_LEFT];
                        break;
                    case SDLK_RIGHT:
                        cur_surf = keypress_surf[SURFACE_RIGHT];
                        break;
                    default:
                        cur_surf = keypress_surf[SURFACE_DEFAULT];
                        break;
                }

                SDL_BlitSurface(cur_surf, NULL, default_surf, NULL);
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    close();

    return 0;
}