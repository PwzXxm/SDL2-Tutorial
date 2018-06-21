# Lesson 13

Set alpha value of texture in order to fade in and fade out.

``` cpp
int SDL_SetTextureBlendMode(SDL_Texture*  texture,
                            SDL_BlendMode blendMode);

int SDL_SetTextureAlphaMod(SDL_Texture* texture,
                           Uint8        alpha);
```

| Value               | Description       |
| ------------------- | ----------------- |
| SDL_BLENDMODE_NONE  | no blending       |
| SDL_BLENDMODE_BLEND | alpha blending    |
| SDL_BLENDMODE_ADD   | additive blending |
| SDL_BLENDMODE_MOD   | color modulate    |