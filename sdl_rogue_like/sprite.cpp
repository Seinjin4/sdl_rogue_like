#include "sprite.h"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ADT/Vector2/Vector2.h"

sprite::sprite(SDL_Renderer *renderer, const std::string path, Vector2 scale) : renderer(renderer), scale(scale), texture(nullptr)
{
    set_texture(path);
}

sprite::~sprite()
{
    SDL_DestroyTexture(texture);
}

SDL_Renderer *sprite::get_renderer() const
{
    return renderer;
}

SDL_Texture *sprite::get_texture() const
{
    return texture;
}

Vector2 sprite::get_scale() const
{
    return scale;
}

void sprite::set_scale(Vector2 scale)
{
    this->scale = scale;
}

void sprite::set_texture(const std::string path)
{

    SDL_Surface *surface = nullptr;
    surface = IMG_Load(path.c_str());

    if (!surface)
    {
        std::cout << path << " : surface error." << std::endl;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture)
    {
        std::cout << path << " : texture error." << std::endl;
    }

    SDL_FreeSurface(surface);
}

void sprite::draw(Vector2 position) const
{
    SDL_Rect rect;
    rect.x = position.get_x();
    rect.y = position.get_y();
    rect.w = scale.get_x();
    rect.h = scale.get_y();

    if (texture)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 200, 0, 200, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void sprite::draw(Vector2 position, int r, int g, int b) const
{
    SDL_Rect rect;
    rect.x = position.get_x();
    rect.y = position.get_y();
    rect.w = scale.get_x();
    rect.h = scale.get_y();

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}
