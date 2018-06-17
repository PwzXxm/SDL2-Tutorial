#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 768;

int main(int argc, char *args[])
{
    SDL_Window *window = NULL;

    SDL_Surface *surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL cannot be initialized: " << SDL_GetError() << std::endl;
    }
    else
    {
        window = SDL_CreateWindow(
            "SDL Lesson1",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            std::cout << "SDL cannot create window: " << SDL_GetError() << std::endl;
        }
        else
        {
            surface = SDL_GetWindowSurface(window);
            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(5000);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}