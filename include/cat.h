#ifndef CAT_H
#define CAT_H

#include "texture.h"
#include "utils.h"

#include <obj/model.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_CATS 1

typedef struct Cat
{
    Model model;
    GLuint texture;
    float rotation, new_rotation;
    float speed;
    vec3 position;
    int decision_time;
} Cat;

void cat_ai_handler(Cat* cat, int elapsed_time);

void move_cat(Cat* cat);

#endif /* CAT_H */
