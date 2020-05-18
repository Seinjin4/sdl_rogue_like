#pragma once

#include <vector>
#include <unordered_set>

#include "ADT/Vector2/Vector2.h"
// #include "game_object.h"

class game_object;

class collider
{
private:
  // static std::map<int, collider*> instances;
  static std::unordered_set<collider*> instances;

  Vector2 scale;
  int layer;


public:
  game_object* parent;

  collider();
  collider(game_object* parent, Vector2 scale,  const int layer);
  ~collider();

  Vector2 get_scale() const;
  int get_layer() const;
  static const std::unordered_set<collider*>& get_instances();

  void set_layer(const int layer);
  void set_scale(Vector2 scale);

  std::vector<collider*> get_collisions() const; // array
  // std::array<int, collider::instances.size()> get_collisions() const;


  bool is_colliding(collider *coll) const;

};
