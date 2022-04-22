#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <obj/transform.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cat), "assets/models/cat.obj");
    scale_model(&(scene->cat), 0.5, 0.5, 0.5);
    scene->texture_cat = load_texture("assets/textures/cat.jpg");

    load_model(&(scene->ttrack), "assets/models/ttrack.obj");
    scale_model(&(scene->ttrack), 1, 1, 1);
    scene->texture_ttrack = load_texture("assets/textures/ttrack.jpg");

    load_model(&(scene->train), "assets/models/train.obj");
    scale_model(&(scene->train), 0.1, 0.1, 0.1);
    scene->texture_train = load_texture("assets/textures/train.jpg");
    

    //glBindTexture(GL_TEXTURE_2D, scene->texture_cat);

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{
}

void render_scene(Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    
   /* int i,j;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            glPushMatrix();
            glTranslatef(i,j,0);
            glScalef(0.01, 0.01, 0.01);
            draw_model(&(scene->cat));
            glPopMatrix();
        }
    }*/

    glPushMatrix();
    glRotatef(scene->cat_rotation,0,0,1);
    glTranslatef(1,0,0);
    //glRotatef(scene->cat_rotation*5,0,0,1);
    scene->cat_rotation -= scene->elapsed_time;
    glBindTexture(GL_TEXTURE_2D, scene->texture_cat);
    draw_model(&(scene->cat));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_ttrack);
    draw_model(&(scene->ttrack));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_train);
    draw_model(&(scene->train));
    glPopMatrix();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
