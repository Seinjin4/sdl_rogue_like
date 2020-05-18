#include "projectile.h"

#include "game_window.h"
#include "game_object.h"
#include "ADT/Vector2/Vector2.h"
#include <iostream>
#include "time_manager.h"
#include "player.h"
#include "collider.h"

//                                    PROJECTILE

projectile::projectile(game_window* gw, const std::string sprite_path, Vector2 scale, Vector2 position, Vector2 direction) : 
    game_object(gw, position),
    object_collider(this, scale, 1),
    object_sprite(new sprite(gw->get_renderer(),sprite_path, scale)), //allocates memory in runtime, not good
    distance_traveled(0),
    damage(1.0),
    max_travel_distance(700),
    movement_speed(700),
    direction(direction)
{   

    // std::cout << direction << std::endl;

    if(direction.get_x() == 0)
    {
        this->position = this->position + Vector2(20,0);
    }

    if(direction.get_y() > 0 || direction.get_x() < 0)
    {
        this->position = this->position + Vector2(0,15);
    }

    if(direction.get_x() > 0)
    {
        this->position = this->position + Vector2(40,15);
    }
}

projectile::~projectile()
{
}

void projectile::move()
{
    if(distance_traveled >= max_travel_distance) kill(); //!

    Vector2 offset = direction * movement_speed;

    offset = offset * time_manager::get_delta_time();
    position = position + offset;

    distance_traveled += offset.magnitude();
}

void projectile::draw() const
{
    object_sprite->draw(position);
}

void projectile::update()
{
    if(distance_traveled >= max_travel_distance)
    {
        kill();
    }
    move();
}

float projectile::get_damage() const
{
    return damage;
}

//                                      TEAR_DEFAULT
//...