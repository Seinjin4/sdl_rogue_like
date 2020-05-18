#pragma once

#include "game_object.h"

#include "ADT/Vector2/Vector2.h"
#include "game_window.h"
#include "sprite.h"

#include <vector>
#include <memory>

class UI_element : public game_object
{
    private:
        static std::vector<UI_element*> instances;

    public:
        UI_element(game_window* gw, Vector2 position);
        ~UI_element();

        static std::vector<UI_element*> get_instances();

        void update() = 0;
        void draw() const = 0;
};


class health_bar : public UI_element
{
    private:
        std::shared_ptr<sprite> health;
        const std::shared_ptr<sprite> background;

        const float max_health_points;
        float health_points;
        const Vector2 base_scale;
    
    public:
        health_bar(game_window* gw, Vector2 position, float max_health_points, float health_points);
        ~health_bar();

        void set_health(float health_points);
        void update();
        void draw() const;
};