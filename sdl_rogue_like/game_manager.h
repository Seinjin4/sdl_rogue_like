#pragma once

#include "game_window.h"
#include "player.h"
#include "enemy.h"
#include "time_manager.h"
#include "UI_element.h"

#include <vector>
#include <map>
#include <memory>

class game_manager
{
private:
  game_window window;

  player *player_object;
  std::vector<enemy *> enemies;

  int framecount;
  float time_passed;

  std::map < std::string , std::shared_ptr<sprite>> game_sprites;

  // UI_object

  health_bar* hb;

public:
  game_manager();
  ~game_manager();

  void initialize();

  void start();

  void update();

  void end();

  void close();
};
