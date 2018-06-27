# Lesson 14

Vsync and frame

``` cpp
SDL_Renderer* SDL_CreateRenderer(SDL_Window* window,
                                 int         index,
                                 Uint32      flags)

```

Flags to Vsync: `SDL_RENDERER_PRESENTVSYNC`