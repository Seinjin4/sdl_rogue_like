#include "enemy.h"
#include "SDL2/SDL_image.h"
#include "game_object.h"
#include "projectile.h"
#include "player.h"
#include <iostream>

enemy::enemy(game_window* gw, std::shared_ptr<sprite> object_sprite, Vector2 scale, Vector2 position) :
  character(gw,object_sprite,scale,position)
{
  movement_speed = 200.0f;
  copy_delay = 5;
  time_since_copy = 0;
}

enemy::enemy(game_window* gw, const std::string sprite_path, Vector2 scale, Vector2 position) :
  character(gw,sprite_path,scale,position)
{
  movement_speed = 200.0f;
  copy_delay = 5;
  time_since_copy = 0;
}

enemy::enemy(const enemy& other) : character(other)
{
  copy_delay = other.copy_delay;
  time_since_copy = 0;
}

enemy::~enemy()
{
}

void enemy::draw() const
{
  object_sprite->draw(position);
}

void enemy::get_player_direction()
{
  for(typename std::unordered_set<character*>::const_iterator i = character::get_instances().begin(); i != character::get_instances().end(); i++)
  {
    if(player* pl = dynamic_cast<player*>(*i))
    {
      Vector2 dir = pl->get_position() - this->position;
      dir.normalize();
      velocity = dir;                         
      break;
    }
    else
    {
      velocity = Vector2(0,0);
    }
  }
}

void enemy::move()
{
  if (velocity.magnitude() != 0)
  {
    velocity.normalize();
    Vector2 offset = velocity * movement_speed;
    offset = offset * time_manager::get_delta_time();
    position = position + offset;
    std::vector<collider*> coll = object_collider.get_collisions();

    position = position - offset;
    if(coll.size() > 0)
    {
      for(size_t i=0; i<coll.size(); i++)
      {
        if(dynamic_cast<player*>(coll[i]->parent)) continue;
        if(character* ch = dynamic_cast<character*>(coll[i]->parent))
        {
            Vector2 orig_position = position;

            Vector2 dist = orig_position - ch->get_position();
            Vector2 dir;

            //CHECK IF COLLIDER FROM Y DIRECTION
            if(dist.get_x() > -object_collider.get_scale().get_x() && dist.get_x() < coll[i]->get_scale().get_x())
            {
              if(dist.get_y() > 0 && offset.get_y() < 0)
              {
                 offset.set_y(0);
                 dir = Vector2(0,1);

              }

              if(dist.get_y() < 0 && offset.get_y() > 0)
              {
                offset.set_y(0);
                dir = Vector2(0,-1);
              }
            }

            //CHECK IF COLLIDER FROM X DIRECTION
            if(dist.get_y() > -coll[i]->get_scale().get_y() && dist.get_y() < object_collider.get_scale().get_y())
            {
              if(dist.get_x() > 0 && offset.get_x() < 0)
              {
                offset.set_x(0);
                dir = Vector2(1,0);
              }

              if(dist.get_x() <0 && offset.get_x() > 0)
              {
                offset.set_x(0);
                dir = Vector2(-1,0);
              }
            }
        }
      }
    }
     position = position + offset;
  }
}

void enemy::update()
{
  get_player_direction();
  move();
  if(copy_delay <= time_since_copy)
  {
   // copy();
    time_since_copy = 0;
  }

  time_since_copy += time_manager::get_delta_time();
  std::vector<collider*> coll = object_collider.get_collisions();

  if(coll.size() != 0)
  {
    for(size_t i=0; i< coll.size(); i++)
    {
      if(projectile* proj = dynamic_cast<projectile*>(coll[i]->parent))
      {
        // proj->kill();
        this->do_damage(proj->get_damage());
        proj->kill();
      }
    }
  }
}

void enemy::copy()
{
  new enemy(*this);
}