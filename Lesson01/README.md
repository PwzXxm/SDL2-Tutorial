# Note

On macOS Command Line, `SDL_Delay()` will not draw the window bar properly. Instead, we can use a loop to detect quit event.

``` c++
bool loop = true;
while(loop)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            loop = false;
        }
    }
}
```