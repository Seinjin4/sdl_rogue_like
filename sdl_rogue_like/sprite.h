#pragma once

#include <stdio.h>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "ADT/Vector2/Vector2.h"

class sprite
{
private:
    SDL_Renderer *renderer;

    Vector2 scale;
    SDL_Texture *texture;

public:
    //sprite(const sprite&) = delete;
    // sprite(SDL_Renderer *renderer, const std::string path);
    sprite(SDL_Renderer *renderer, const std::string path, Vector2 scale);
    ~sprite();

    void draw(Vector2 position) const;
    void draw(Vector2 position, int r, int g, int b) const;

    SDL_Texture *get_texture() const;
    Vector2 get_scale() const;
    SDL_Renderer *get_renderer() const;

    void set_scale(Vector2 scale);
    void set_texture(const std::string path);
};