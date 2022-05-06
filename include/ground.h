#ifndef GROUND_H
#define GROUND_H

#include <obj/draw.h>
#include <obj/transform.h>
#include <obj/model.h>
#include "texture.h"
#include "utils.h"

typedef struct Ground
{
    Model model;
    GLuint texture;
    vec3 position;
    float size;
} Ground;

void init_ground(Ground* ground, char* filename, char* modelname, float x, float y);

void render_ground(Ground* ground);

#endif /* GOUND_H */