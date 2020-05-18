#pragma once

#include "ADT/Vector2/Vector2.h"

// #include <vector>
#include <unordered_set>
#include <memory>

#include "sprite.h"
#include "collider.h"
#include "game_window.h"

class collider;
//--------------------- BASE GAME_OBJECT

class game_object
{
private:
  static std::unordered_set<game_object*> instances;

protected:

  game_window *gw;
  Vector2 position;

  bool f_is_alive;

public:
  game_object(game_window* gw, Vector2 position);
  game_object(const game_object& other);

  virtual ~game_object();

  static const std::unordered_set<game_object*>& get_instances();

  virtual void update() = 0;
  virtual void draw() const = 0;
  void kill();

  bool is_alive() const;

  Vector2 get_position() const;
  game_window* get_game_window() const;

  void set_position(Vector2 position); 
};



//------------------------ GAME CHARACTER

class character : public game_object
{
private:
  // static std::vector<character*> instances;
  static std::unordered_set<character*> instances;

protected:
  collider object_collider;
  std::shared_ptr<sprite> object_sprite;

  Vector2 velocity;
  Vector2 attack_direction;

  float health;
  double movement_speed;

public:
  character(game_window* gw, const std::string sprite_path, Vector2 scale, Vector2 position);
  character(game_window* gw, std::shared_ptr<sprite> object_sprite, Vector2 scale, Vector2 position);

  character(const character & other);

  ~character();

  // static const std::vector<character*>& get_instances();
  static const std::unordered_set<character*>& get_instances();

  void update() = 0;
  virtual void move() = 0;
  void draw() const;
  virtual void do_damage(float damage);

  float get_health() const;

};