#ifndef CAT_H
#define CAT_H

#include "texture.h"
#include "utils.h"

#include <obj/model.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_CATS 6
#define ROAD_START 1.5
#define ROAD_END 4.9

typedef struct Cat
{
    Model model;
    GLuint texture;
    float rotation, new_rotation;
    float speed;
    vec3 position;
    int decision_time;
    bool is_grabbed;
    bool is_dead;
} Cat;

void cat_ai_handler(Cat* cat, uint32_t elapsed_time);

void move_cat(Cat* cat, uint32_t elapsed_time);

void relocate_cat(Cat* cat, float x, float y);

void spawn_point_generator(Cat* cat);

void init_cat(Cat* cat);



#endif /* CAT_H */
