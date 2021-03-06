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
            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
            SDL_UpdateWindowSurface(window);

            // SDL_Delay() will not draw the window properly
            bool loop = true;
            while (loop) {
                SDL_Event e;
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        loop = false;
                    }
                }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}