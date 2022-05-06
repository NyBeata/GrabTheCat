#ifndef BUS_H
#define BUS_H

#include "texture.h"
#include "utils.h"

#include <obj/model.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct Bus
{
    Model model;
    GLuint texture;
    float rotation, new_rotation;
    float speed;
    vec3 position;
    int cooldown;
} Bus;

void init_bus(Bus* bus);

void spawn_bus(Bus* bus);

void move_bus(Bus* bus, uint32_t elapsed_time);

#endif /* BUS_H */
