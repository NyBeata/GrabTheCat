#include "ground.h"

void init_ground(Ground* ground, char* filename, int length, int width, int x, int y)
{
    ground->length = length;
    ground->width = width;

    ground->position.x = x;
    ground->position.y = y;

    load_model(&(ground->model), "assets/models/cube.obj");
    ground->texture = load_texture(filename);
}

void render_ground(Ground* ground)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ground->texture);
    glTranslatef(ground->position.x, ground->position.y, -1);
    for(int i=0; i < ground->width; i++){
        for(int j=0; j < ground->length; j++){
            glPushMatrix();
            glTranslatef(i, j, 0);
            draw_model(&(ground->model));
            glPopMatrix();
        }
    }
    glPopMatrix();
    
}