#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

const int kWidth = 1024;
const int kHeight = 768;

class MyTexture {
public:
    MyTexture();
    ~MyTexture();
    bool Load(std::string);
    void Free();
    void SetColor(Uint8, Uint8, Uint8);
    void Render(int, int);

    int GetWidth();
    int GetHeight();

private:
    SDL_Texture *texture;
    int w;
    int h;
};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
MyTexture color_texture;

MyTexture::MyTexture() {
    texture = NULL;
    w = 0;
    h = 0;
}

MyTexture::~MyTexture() { Free(); }

bool MyTexture::Load(std::string path) {
    Free();

    SDL_Surface *load_surface = IMG_Load(path.c_str());
    if (load_surface == NULL) {
        std::cerr << "Failed to load surface: " << IMG_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, load_surface);
    if (texture == NULL) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return false;
    }

    w = load_surface->w;
    h = load_surface->h;

    SDL_FreeSurface(load_surface);

    return true;
}

void MyTexture::Free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        w = 0;
        h = 0;
    }
}

void MyTexture::SetColor(Uint8 r, Uint8 g, Uint8 b) { SDL_SetTextureColorMod(texture, r, g, b); }

void MyTexture::Render(int x, int y) {
    SDL_Rect render_rect = {x, y, w, h};

    SDL_RenderCopy(renderer, texture, NULL, &render_rect);
}

int MyTexture::GetWidth() { return w; }

int MyTexture::GetHeight() { return h; }

bool Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Unable to init: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "SDL2 Lesson 12 Color Modulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kWidth, kHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Failed to create render: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    int img_flag = IMG_INIT_PNG;
    if ((IMG_Init(img_flag) & img_flag) != img_flag) {
        std::cerr << "Failed to init IMG: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

bool LoadMedia() {
    if (!color_texture.Load("../img/modulation.png")) {
        std::cerr << "Failed to load PNG" << std::endl;
        return false;
    }
    return true;
}

void Close() {
    color_texture.Free();

    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
    if (!Init()) {
        std::cerr << "Failed to Init()" << std::endl;
        return -1;
    }

    if (!LoadMedia()) {
        std::cerr << "Failed to load media" << std::endl;
        return -1;
    }

    bool loop = true;
    SDL_Event e;
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;

    while (loop) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        r += 32;
                        break;
                    case SDLK_w:
                        g += 32;
                        break;
                    case SDLK_e:
                        b += 32;
                        break;
                    case SDLK_a:
                        r -= 32;
                        break;
                    case SDLK_s:
                        g -= 32;
                        break;
                    case SDLK_d:
                        b -= 32;
                        break;
                    default:
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        color_texture.SetColor(r, g, b);
        color_texture.Render(0, 0);

        SDL_RenderPresent(renderer);
    }

    Close();

    return 0;
}