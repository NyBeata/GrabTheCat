#include "bus.h"

void init_bus(Bus* bus)
{
    load_model(&(bus->model), "assets/models/bus.obj");
    bus->texture = load_texture("assets/textures/bus.jpg");
    spawn_bus(bus);

    bus->speed = 0.01;
    bus->position.z = -0.2;
    /*bus->position.x = 1.5;
    bus->position.y = 0;
    bus->rotation = 0;
    bus->cooldown = 0;*/
}

void spawn_bus(Bus* bus)
{
    int LoR = (rand() %(1 - 0 + 1)) + 0;

    if(LoR == 0){
        bus->position.x = 3.1;
        bus->position.y = 10;
        bus->rotation = 180;
    } else {
        bus->position.x = 1.6;
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