#include "game_object.h"
#include "time_manager.h"

#include <memory>
#include <unordered_set>


std::unordered_set<character*> character::instances;

character::character(game_window* gw, const std::string sprite_path, Vector2 scale, Vector2 position) :
    game_object(gw, position),
    object_collider(this, scale, 1),
    object_sprite(new sprite(gw->get_renderer(),sprite_path, scale)), 
    health(3.0f)
{
    instances.insert(this);
}

character::character(game_window* gw, std::shared_ptr<sprite> object_sprite, Vector2 scale, Vector2 position) : 
    game_object(gw, position),
    object_collider(this, scale, 1),
    object_sprite(object_sprite),
    health(3.0f)
{
    instances.insert(this);
}
character::character(const character & other) : game_object(other)
{
    this->position = this->position + other.object_sprite->get_scale() + Vector2(1,1);
    this->object_sprite = other.object_sprite;
    this->object_collider = collider(this,other.object_collider.get_scale(),1);
    this->health = other.health; 
    this->movement_speed = other.movement_speed;

    instances.insert(this);
}


character:: ~character()
{
    instances.erase(this);
}

void character::draw() const
{
    object_sprite->draw(position);
}

const std::unordered_set<character*>& character::get_instances()
{
    return instances;
}

void character::move()
{
    if (velocity.magnitude() != 0)
  {
    velocity.normalize();
    Vector2 offset = velocity * movement_speed;
    offset = offset * time_manager::get_delta_time();
    position = position + offset;

    std::vector<collider*> coll = object_collider.get_collisions();
    if(coll.size() != 0)
    {

      //std::cout << "player collides" << std::endl;
      for(size_t i=0; i<coll.size(); i++)
      {

        if(character* ch = dynamic_cast<character*>(coll[i]->parent))
        {
            Vector2 dir = ch->get_position() - position;
            dir = dir * movement_speed * time_manager::get_delta_time();
            position = position - (offset - dir);

          // Also do some DAMAGE
        }
      }
    }
  }
}

void character::do_damage(float damage)
{
    health -= damage;
    if(health <= 0)
    {
        kill();
    }
}

float character::get_health() const
{
    return health;
}