#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "cat.h"
#include "ground.h"
#include <SDL2/SDL.h>
#include <obj/model.h>
#include <stdint.h>

typedef struct Scene
{
    Cat cats[MAX_CATS];
    Ground pavement;
    Material material;
    uint32_t base_time;
    uint32_t elapsed_time;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void get_elapsed_time(Scene* scene);

#endif /* SCENE_H */
