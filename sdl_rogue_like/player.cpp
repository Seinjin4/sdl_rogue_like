#include "player.h"
#include "time_manager.h"
#include "projectile.h"
#include "collider.h"

#include <iostream>

player::player(game_window* gw, std::shared_ptr<sprite> object_sprite, Vector2 scale, Vector2 position) :
   character(gw,object_sprite,scale,position)
{
  movement_speed = 500.0f;
  attack_speed = 0.5f;
  time_since_last_attack = attack_speed;
  invulnurable_time = 1.0f;
  current_invulnurable_time = 1.0f;

}

player::player(game_window* gw, const std::string sprite_path, Vector2 scale, Vector2 position) : 
  character(gw,sprite_path,scale,position)
{
  movement_speed = 500.0f;
  attack_speed = 0.5f;
  time_since_last_attack = attack_speed;
  invulnurable_time = 1.0f;
  current_invulnurable_time = 1.0f;

}

player::~player()
{
}

void player::get_movement_input()
{
  const auto state = SDL_GetKeyboardState(NULL);

  SDL_PumpEvents();

  // Horizontal movement
  if((state[SDL_SCANCODE_A] && state[SDL_SCANCODE_D]) || (!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]))
  {
      velocity.set_x(0);
  }
  else if(state[SDL_SCANCODE_A])
  {
    velocity.set_x(-1);
  }
  else if(state[SDL_SCANCODE_D])
  {
    velocity.set_x(1);
  }

  // Vertical movement
  if((state[SDL_SCANCODE_W] && state[SDL_SCANCODE_S]) || (!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S]))
  {
      velocity.set_y(0);
  }
  else if(state[SDL_SCANCODE_W])
  {
    velocity.set_y(-1);
  }
  else if(state[SDL_SCANCODE_S])
  {
    velocity.set_y(1);
  }
}

void player::get_attack_input() // Feel like SDL_KEYDOWN is better for attack animations than keyboard_state edit: ITS NOT
{
  const auto state = SDL_GetKeyboardState(NULL);

  SDL_PumpEvents();

  // Horizontal attack direction
  if((state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_RIGHT]) || (!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT]))
  {
    attack_direction.set_x(0);
  }
  else if(state[SDL_SCANCODE_LEFT])
  {
    attack_direction.set_x(-1);
    return;
  }
  else if(state[SDL_SCANCODE_RIGHT])
  {
    attack_direction.set_x(1);
    return;
  }

  // Vertical attack direction
  if((state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_DOWN]) || (!state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN]))
  {
    attack_direction.set_y(0);
  }
  else if(state[SDL_SCANCODE_UP])
  {
    attack_direction.set_y(-1);
    return;
  }
  else if(state[SDL_SCANCODE_DOWN])
  {
    attack_direction.set_y(1);
    return;
  }
}

void player::move()
{
  if (velocity.magnitude() != 0)
  {
    velocity.normalize();
    Vector2 offset = velocity * movement_speed;
    offset = offset * time_manager::get_delta_time();
    position = position + offset;

    std::vector<collider*> coll = object_collider.get_collisions();

    position = position - offset;
    if(coll.size() != 0)
    {

      //std::cout << "player collides" << std::endl;
      for(size_t i=0; i<coll.size(); i++)
      {
        if(dynamic_cast<character*>(coll[i]->parent)) // character* ch = dynamic_cast<character*>(coll[i]->parent)
        {
            // Vector2 orig_position = position;

            // Vector2 dist = orig_position - ch->get_position();
            // Vector2 dir;

            // //CHECK IF COLLIDER FROM Y DIRECTION
            // if(dist.get_x() > -object_collider.get_scale().get_x() && dist.get_x() < coll[i]->get_scale().get_x())
            // {
            //   // std::cout << "Y HIT" << std::endl;
            //   // offset.set_x(0);

            //   if(dist.get_y() > 0 && offset.get_y() < 0)
            //   {
            //      offset.set_y(0);
            //      dir = Vector2(0,1);

            //   }

            //   else if(dist.get_y() < 0 && offset.get_y() > 0)
            //   {
            //     offset.set_y(0);
            //     dir = Vector2(0,-1);
            //   }
            // }

            // if(dist.get_y() > -coll[i]->get_scale().get_y() && dist.get_y() < object_collider.get_scale().get_y())
            // {
            //   // std::cout << "X HIT" << std::endl;
            //   //offset.set_y(0);

            //   if(dist.get_x() > 0 && offset.get_x() < 0)
            //   {
            //     offset.set_x(0);
            //     dir = Vector2(1,0);
            //   }

            //   else if(dist.get_x() < 0 && offset.get_x() > 0)
            //   {
            //     offset.set_x(0);
            //     dir = Vector2(-1,0);
            //   }
            // }
            if(current_invulnurable_time >= invulnurable_time)
            {
              do_damage(0.5f);
              current_invulnurable_time = 0.0;
            }
        }
      }
    }
     position = position + offset;
  }
}

void player::attack()
{
  if(attack_direction.magnitude() != 0)
  {
    if(time_since_last_attack >= attack_speed)
    {
      time_since_last_attack = 0;
      new projectile(gw,"sprites/tear_sprite.png",Vector2(20,20),position,attack_direction);
    }
      attack_direction = Vector2(0,0);
  }
}

void player::update()
{
  current_invulnurable_time += time_manager::get_delta_time();
  time_since_last_attack += time_manager::get_delta_time();
  get_movement_input();
  get_attack_input();
  move();
  attack();
}