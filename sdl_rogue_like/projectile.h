#pragma once

#include "game_object.h"
#include "collider.h"
#include "sprite.h"

// class player;

class projectile : public game_object
{
    private:
        collider object_collider;
        std::shared_ptr<sprite> object_sprite;


        int distance_traveled;

        float damage;
        int max_travel_distance;
        int movement_speed;

        Vector2 direction;

        void move();
    
    public:
        projectile(game_window* gw,const std::string sprite_path, Vector2 scale, Vector2 position, Vector2 direction);

        ~projectile();
        void draw() const;
        void update();

        float get_damage() const;
};