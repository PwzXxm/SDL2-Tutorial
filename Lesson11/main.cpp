#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

const int kWidth = 1024;
const int kHeight = 768;
const int kSpritePos[4][4] = {0, 0, 100, 100, 100, 0, 100, 100, 0, 100, 100, 100, 100, 100, 100, 100};

class MyTexture {
public:
    MyTexture();
    ~MyTexture();
    bool Load(std::string);
    void Render(int, int, SDL_Rect *);
    void Free();

    int GetWidth();
    int GetHeight();

private:
    SDL_Texture *texture;
    int w;
    int h;
};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Rect sprite_rect[4];
MyTexture sprite_sheet_texture;

MyTexture::MyTexture() {
    texture = NULL;
    w = 0;
    h = 0;
}

MyTexture::~MyTexture() { Free(); }

bool MyTexture::Load(std::string path) {
    Free();
    SDL_Texture *new_texture = NULL;

    SDL_Surface *load_surface = IMG_Load(path.c_str());
    if (load_surface == NULL) {
        std::cerr << "Failed to load surface " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0, 0xff, 0xff));

    new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
    if (new_texture == NULL) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return false;
    }

    w = load_surface->w;
    h = load_surface->h;

    SDL_FreeSurface(load_surface);

    texture = new_texture;
    return true;
}

void MyTexture::Render(int x, int y, SDL_Rect *rect) {
    SDL_Rect render_rect = {x, y, w, h};

    if (rect != NULL) {
        render_rect.w = rect->w;
        render_rect.h = rect->h;
    }

    SDL_RenderCopy(renderer, texture, rect, &render_rect);
}

void MyTexture::Free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        w = h = 0;
    }
}

int MyTexture::GetWidth() { return w; }

int MyTexture::GetHeight() { return h; }

bool LoadMedia() {
    if (!sprite_sheet_texture.Load("../img/sprite_sheet.png")) {
        std::cerr << "Failed to load bg" << std::endl;
        return false;
    }

    for (int i = 0; i < 4; i++) {
        std::cout << i << ": ";
        for (int j = 0; j < 4; j++) {
            std::cout << kSpritePos[i][j] << " ";
        }
        std::cout << std::endl;
        sprite_rect[i].x = kSpritePos[i][0];
        sprite_rect[i].y = kSpritePos[i][1];
        sprite_rect[i].w = kSpritePos[i][2];
        sprite_rect[i].h = kSpritePos[i][3];
    }

    return true;
}

bool Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to init video: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Lesson 11 Clip Rendering and Sprite Sheets",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              kWidth,
                              kHeight,
                              SDL_WINDOW_SHOWN);
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
    while (loop) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        sprite_sheet_texture.Render(0, 0, &sprite_rect[0]);
        sprite_sheet_texture.Render(kWidth - sprite_rect[1].w, 0, &sprite_rect[1]);
        sprite_sheet_texture.Render(0, kHeight - sprite_rect[2].h, &sprite_rect[2]);
        sprite_sheet_texture.Render(kWidth - sprite_rect[3].w, kHeight - sprite_rect[3].h, &sprite_rect[3]);

        SDL_RenderPresent(renderer);
    }

    Close();

    return 0;
}