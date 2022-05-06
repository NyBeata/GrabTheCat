#include "ground.h"

void init_ground(Ground* ground, char* filename, char* modelname, float x, float y)
{
    ground->position.x = x;
    ground->position.y = y;

    load_model(&(ground->model), modelname);
    ground->texture = load_texture(filename);
}

void render_ground(Ground* ground)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ground->texture);
    glTranslatef(ground->position.x, ground->position.y, -0.5);
    draw_model(&(ground->model));
    glPopMatrix();
    
}