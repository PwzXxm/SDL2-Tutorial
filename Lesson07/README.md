``` cpp
SDL_Renderer* SDL_CreateRenderer(SDL_Window* window,
                                 int         index,
                                 Uint32      flags);

SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

int SDL_SetRenderDrawColor(SDL_Renderer* renderer,
                           Uint8         r,
                           Uint8         g,
                           Uint8         b,
                           Uint8         a);

SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer,
                                          SDL_Surface*  surface);

int SDL_RenderClear(SDL_Renderer* renderer);

int SDL_RenderCopy(SDL_Renderer*   renderer,
                   SDL_Texture*    texture,
                   const SDL_Rect* srcrect,
                   const SDL_Rect* dstrect);

void SDL_RenderPresent(SDL_Renderer* renderer);

void SDL_DestroyRenderer(SDL_Renderer* renderer)
void SDL_DestroyTexture(SDL_Texture* texture)
```