#include "bus.h"

void init_bus(Bus* bus)
{
    load_model(&(bus->model), "assets/models/bus.obj");
    bus->texture = load_texture("assets/textures/bus.jpg");
    spawn_bus(bus);

    bus->speed = 0.01;
    bus->position.z = -0.5;
}

void spawn_bus(Bus* bus)
{
    // jobb vagy bal oldal eldöntése
    int LoR = (rand() %(1 - 0 + 1)) + 0;

    if(LoR == 0){
        bus->position.x = 4;
        bus->position.y = 10;
        bus->rotation = 180;
    } else {
        bus->position.x = 2;
        bus->position.y = -10;
        bus->rotation = 0;
    }

    bus->cooldown = (rand() %(10000 - 5000 + 1)) + 5000;
}

void move_bus(Bus* bus, uint32_t elapsed_time)
{
    if(bus->cooldown > 100){
        bus->cooldown -= elapsed_time;
    } else if(bus->position.y > 10 || bus->position.y < -10){
        spawn_bus(bus);
    } else {
        if(bus->rotation == 0){
            bus->position.y += bus->speed * elapsed_time;
        } else {
            bus->position.y -= bus->speed * elapsed_time;
        }
    }
}