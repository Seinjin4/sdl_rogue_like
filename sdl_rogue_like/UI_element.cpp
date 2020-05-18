#include "UI_element.h"

#include "ADT/Vector2/Vector2.h"
#include "game_window.h"
#include "sprite.h"

#include <vector>
#include <memory>


//                                   UI_ELEMENT CLASS

std::vector<UI_element*>UI_element::instances;

UI_element::UI_element(game_window* gw, Vector2 position):
    game_object(gw, position)
{
    instances.push_back(this);
}

UI_element::~UI_element()
{
    for(size_t i=0; i< instances.size();i++)
    {
        if(instances[i] == this)
        {
            instances.erase(instances.begin() + i);
            break;
        }
    }
}

std::vector<UI_element*> UI_element::get_instances()
{
    return instances;
}


//                                   HEALTH_BAR CLASS

health_bar::health_bar(game_window* gw, Vector2 position, float max_health_points, float health_points) :
    UI_element(gw, position),
    health(new sprite(gw->get_renderer(),"",Vector2(200,30))),
    background(new sprite(gw->get_renderer(),"",Vector2(210,40))),
    max_health_points(max_health_points),
    health_points(health_points),
    base_scale(200,30)
{

}

health_bar::~health_bar()
{

}

void health_bar::set_health(float health_points)
{
    this->health_points = health_points;
}

void health_bar::update()
{
    Vector2 health_size = Vector2(base_scale.get_x() * health_points / max_health_points, base_scale.get_y());
    health->set_scale(health_size);
}

void health_bar::draw() const
{
    Vector2 background_pos = Vector2(position.get_x() - 5, position.get_y() - 5);
    background->draw(background_pos,0,0,0);
    health->draw(position,255,0,0);
}



