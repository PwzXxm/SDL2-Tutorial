# Lesson 08

## Coordinate system

```
          x
   0 1 2 3 4 5 6 7 8
   1  -------------->
   2 |
   3 |
   4 |
y  5 |
   6 |
   7 |
   8 |
     \/

```

``` cpp
// Rect
SDL_Rect rect = {x, y, w, h};
int SDL_RenderFillRect(SDL_Renderer*   renderer,
                       const SDL_Rect* rect);

// Line
int SDL_RenderDrawLine(SDL_Renderer* renderer,
                       int           x1,
                       int           y1,
                       int           x2,
                       int           y2);

// dotted line
int SDL_RenderDrawPoint(SDL_Renderer* renderer,
                        int           x,
                        int           y);

for (int i = 0; i < HEIGHT; i += 4) {
    SDL_RenderDrawPoint(renderer, WIDTH / 2, i);
}
```
