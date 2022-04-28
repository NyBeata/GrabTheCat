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
    int length;
    int width;
    float size;
} Ground;

void init_ground(Ground* ground, char* filename, int length, int width, int x, int y);

void render_ground(Ground* ground);

#endif /* GOUND_H */