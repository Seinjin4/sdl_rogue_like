#include "collider.h"
#include "game_object.h"

#include <unordered_set>
#include <vector>

std::unordered_set<collider*> collider::instances;

collider::collider() 
  : scale(0,0)
{
  instances.insert(this);
}

collider::collider(game_object* parent, Vector2 scale, const int layer) 
  : parent(parent), scale(scale), layer(layer)
{
  instances.insert(this);
}

collider::~collider()
{
  instances.erase(this);
}

const std::unordered_set<collider*>& collider::get_instances()
{
  return instances;
}


Vector2 collider::get_scale() const
{
  return scale;
}

int collider::get_layer() const
{
  return layer;
}

void collider::set_layer(const int layer)
{
  this->layer = layer;
}

void collider::set_scale(Vector2 scale)
{
  this->scale = scale;
}

bool collider::is_colliding(collider *coll) const // destructor activates when this method ends
{
  int Px = coll->parent->get_position().get_x();
  int Pxw = Px + coll->scale.get_x();
  int Py = coll->parent->get_position().get_y();
  int Pyh = Py + coll->scale.get_y();

  if((Px >= parent->get_position().get_x() && Px <= parent->get_position().get_x() + scale.get_x()) && (Py >= parent->get_position().get_y() && Py <= parent->get_position().get_y() + scale.get_y()))
  {
    return true;
  }

  if((Pxw >= parent->get_position().get_x() && Pxw <= parent->get_position().get_x() + scale.get_x()) && (Py >= parent->get_position().get_y() && Py <= parent->get_position().get_y() + scale.get_y()))
  {
    return true;
  }

  if((Px >= parent->get_position().get_x() && Px <= parent->get_position().get_x() + scale.get_x()) && (Pyh >= parent->get_position().get_y() && Pyh <= parent->get_position().get_y() + scale.get_y()))
  {
    return true;
  }

  if((Pxw >= parent->get_position().get_x() && Pxw <= parent->get_position().get_x() + scale.get_x()) && (Pyh >= parent->get_position().get_y() && Pyh <= parent->get_position().get_y() + scale.get_y()))
  {
    return true;
  }

  return false;
}

// std::array<int, collider::instances.size()> collider::get_collisions() const
// {
//   std::array<int, instances.size()> matches;
//   int n=0;

//   for(typename std::map<int, collisions*>::iterator i = instances.begin(); i != instances.end(); i++)
//   {
//     if(get<collisions*>(*i) == this)
//     {
//       if(this->layer >= get<collisions*>(*i))
//       {
//         if(is_colliding(get<collisions*>(*i)))
//         {
//           matches[n] = get<int>(*i);
//           n++;
//         }
//       }
//     }
//   }
//   return matches;
// }

std::vector<collider*> collider::get_collisions() const
{
  std::vector<collider*> matches;

  for(typename std::unordered_set<collider*>::iterator i = instances.begin(); i != instances.end(); i++)
  {
    if(*i != this)
    {
      if(this->layer >= (*i)->get_layer())
      {
        if(is_colliding(*i))
        {
          matches.push_back(*i);
        }
      }
    }
  }
  return matches;
}