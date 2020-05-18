#pragma once

#include <memory>

#include "game_window.h"
#include "ADT/Vector2/Vector2.h"
#include "time_manager.h"
#include "game_object.h"
#include "sprite.h"


class enemy : public character
{
  private:
    // void move(character* player);
    // void attack(character* player);

    float copy_delay;
    float time_since_copy;

    void copy();

  public:

    enemy(game_window* gw, std::shared_ptr<sprite> object_sprite, Vector2 scale, Vector2 position);
    enemy(game_window* gw, const std::string sprite_path, Vector2 scale, Vector2 position);
    enemy(const enemy& other); //make them clone

    ~enemy();

    void draw() const;
    void update();
    void move();

    void get_player_direction();

};
