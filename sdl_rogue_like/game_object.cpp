
#include "game_object.h"

#include "ADT/Vector2/Vector2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>
// #include <vector>
#include <unordered_set>

#include "sprite.h"

// std::vector<game_object*> game_object::instances;
std::unordered_set<game_object*> game_object::instances;

game_object::game_object(game_window* gw, Vector2 position) :
  gw(gw),
  position(position),
  f_is_alive(true)
{
    instances.insert(this);
}

game_object::game_object(const game_object& other)
{
  this->gw = other.gw;
  this->position = other.position;
  this->f_is_alive = true;

    instances.insert(this);
}

game_object::~game_object()
{
  instances.erase(this);
}

const std::unordered_set<game_object*>& game_object::get_instances()
{
  return instances;
}

void game_object::kill()
{
  f_is_alive = false;
}

bool game_object::is_alive() const
{
  return f_is_alive;
}

Vector2 game_object::get_position() const
{
  return position;
}

game_window* game_object::get_game_window() const
{
  return gw;
}

void game_object::set_position(Vector2 position)
{
  this->position = position;
}
