#include "game_manager.h"

#include "game_window.h"
#include "player.h"
#include "enemy.h"
#include "time_manager.h"
#include "UI_element.h"
#include "sprite.h"

#include <vector>
#include <memory>
#include <map>
#include <utility>

game_manager::game_manager() : framecount(0), time_passed(0)
{
  initialize();
}

game_manager::~game_manager()
{
  std::cout << (float)framecount / time_passed << std::endl;
  for(typename std::unordered_set<game_object*>::const_iterator i = game_object::get_instances().begin(); i != game_object::get_instances().end();)
  {
    game_object* temp = *i;
    i++;
    delete temp;
  }

}

void game_manager::initialize()
{
  game_sprites.insert({"isaac_front", std::shared_ptr<sprite>(new sprite(window.get_renderer(), "sprites/isaac_sprite.png", Vector2(60, 70)))});
  game_sprites.insert({"monster_front", std::shared_ptr<sprite>(new sprite(window.get_renderer(), "sprites/monster_sprite.png", Vector2(60, 70)))});
  game_sprites.insert({"tear_default", std::shared_ptr<sprite>(new sprite(window.get_renderer(), "sprites/tear_sprite.png", Vector2(60, 70)))});


  player_object = new player(&window, game_sprites.find("isaac_front")->second, Vector2(60, 70), Vector2(500, 500));
  enemies.push_back(new enemy(&window, game_sprites.find("monster_front")->second, Vector2(60, 70), Vector2(200, 300)));
  enemies.push_back(new enemy(&window, game_sprites.find("monster_front")->second, Vector2(60, 70), Vector2(800, 600)));
  enemies.push_back(new enemy(&window, game_sprites.find("monster_front")->second, Vector2(60, 70), Vector2(600, 600)));
  enemies.push_back(new enemy(&window, game_sprites.find("monster_front")->second, Vector2(60, 70), Vector2(1000, 400)));
  enemies.push_back(new enemy(&window, game_sprites.find("monster_front")->second, Vector2(60, 70), Vector2(200, 600)));

  hb = new health_bar(&window, Vector2(1000,30),player_object->get_health(),player_object->get_health());
}

void game_manager::update()
{
  while (!window.isClosed())
  {
    time_manager::count_delta_time();
    framecount++;
    time_passed+=time_manager::get_delta_time();


    // std::cout <<"DELTATIME :" << time_manager::get_delta_time() << std::endl;

      for(typename std::unordered_set<game_object*>::const_iterator i = game_object::get_instances().begin(); i != game_object::get_instances().end();)
      {
        if (!(*i)->is_alive())
        {
          game_object* temp = *i;
          i++;
          delete temp;
        }
        else
        {
          i++;
        }
      }
      for(typename std::unordered_set<game_object*>::const_iterator i = game_object::get_instances().begin(); i != game_object::get_instances().end();i++)
      {

        game_object* temp = *i;
        (**i).update();

      }

    hb->set_health(player_object->get_health());

      for(typename std::unordered_set<game_object*>::const_iterator i = game_object::get_instances().begin(); i != game_object::get_instances().end();i++)
      {
        if((*i)->is_alive())
        {
         (**i).draw();
        }
      }

    window.pollEvent();
    window.clear();
  }
}
