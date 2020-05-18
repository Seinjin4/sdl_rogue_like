#pragma once

#include <memory>

#include "game_window.h"
#include "ADT/Vector2/Vector2.h"
#include "time_manager.h"
#include "game_object.h"

class player : public character
{
private:
	float attack_speed; //Delay between shots in seconds
	float time_since_last_attack;

	float invulnurable_time;
	float current_invulnurable_time;

public:

	player(game_window* gw, std::shared_ptr<sprite> object_sprite, Vector2 scale, Vector2 position);
	player(game_window* gw, const std::string sprite_path, Vector2 scale, Vector2 position);
	player(const player&) = delete;

	~player();

	void get_movement_input();
	void get_attack_input();
	void move();
	void attack();
	

	void update();
};
