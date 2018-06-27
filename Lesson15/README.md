# Lesson 15

Rotating and flipping a texture

``` cpp
int SDL_RenderCopyEx(SDL_Renderer*          renderer,
                     SDL_Texture*           texture,
                     const SDL_Rect*        srcrect,
                     const SDL_Rect*        dstrect,
                     const double           angle,
                     const SDL_Point*       center,
                     const SDL_RendererFlip flip)
```

| Values              | Description       |
| ------------------- | ----------------- |
| SDL_FLIP_NONE       | do not flip       |
| SDL_FLIP_HORIZONTAL | flip horizontally |
| SDL_FLIP_VERTICAL   | flip vertically   |
