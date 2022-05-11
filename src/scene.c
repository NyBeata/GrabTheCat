#include "scene.h"

#include <stdio.h>
#include <math.h>

#include <obj/load.h>
#include <obj/draw.h>
#include <obj/transform.h>

void init_scene(Scene* scene)
{
    scene->game_start = load_texture("assets/textures/start.png");
    scene->game_over = load_texture("assets/textures/gameover.png");

    init_ground(&(scene->pavement), "assets/textures/pave.jpg", "assets/models/pave.obj", -1, 0);
    init_ground(&(scene->road), "assets/textures/road.jpg", "assets/models/road.obj", 4, 0);
    init_ground(&(scene->grass), "assets/textures/grass.jpg", "assets/models/grass.obj", 11, 0);

    for (int i=0; i < MAX_CATS; i++){
        init_cat(&(scene->cats[i]));
    }

    init_bus(&(scene->bus));
    

    scene->material.ambient.red = 0.5;
    scene->material.ambient.green = 0.5;
    scene->material.ambient.blue = 0.5;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    scene->score = 0;
    scene->sec = 1000;

    scene->is_start = true;
    scene->is_over = false;
    scene->paused = false;

    scene->final_countdown = 4000;  
}

void set_lighting()
{
    float ambient_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float position[] = { -10.0f, -10.0f, 10.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable (GL_LIGHTING);
    glEnable(GL_LIGHT0);
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
    //pont számolás
    if(scene->sec > 100){
        scene->sec -= scene->elapsed_time;
    } else if (scene->is_over == false) {
        scene->score = scene->score + 1;
        scene->sec += 1000;
    }

    for(int i=0; i < MAX_CATS; i++){
        if(scene->cats[i].is_grabbed == false && scene->cats[i].is_dead == false){
            //macska mozgás
            cat_ai_handler(&(scene->cats[i]), scene->elapsed_time);
            move_cat(&(scene->cats[i]), scene->elapsed_time);
        } else if (scene->cats[i].is_dead == false){
            //macska átpakolás
            relocate_cat(&(scene->cats[i]), scene->cursor_location.x, scene->cursor_location.y);
        }    
    }

    move_bus(&(scene->bus), scene->elapsed_time);

    //ütközés vizsgálat
    for(int i=0; i < MAX_CATS; i++){
        if(fabs(scene->cats[i].position.x - scene->bus.position.x) < 0.65){
            if(fabs(scene->cats[i].position.y - scene->bus.position.y) < 1.1){
            scene->cats[i].is_dead = true;
            scene->is_over = true;
            }
        }
    }
}

void render_scene(Scene* scene)
{
    if(scene->is_start == false && (scene->is_over == false || scene->final_countdown > 100)){
        set_material(&(scene->material));
        set_lighting();

        int x;
        int y;
        SDL_GetMouseState(&x, &y);

        render_ground(&(scene->pavement));
        render_ground(&(scene->road));
        render_ground(&(scene->grass));

        for(int i=0; i < MAX_CATS; i++){
            glPushMatrix();
            glTranslatef(scene->cats[i].position.x, scene->cats[i].position.y, scene->cats[i].position.z);
            glRotatef(scene->cats[i].rotation, 0, 0, 1);
            glBindTexture(GL_TEXTURE_2D, scene->cats[i].texture);
            
            //halott cica kilapítása
            if(scene->cats[i].is_dead == true){
                glTranslatef(0, 0, -0.22);
                glScalef(1.2, 1.5, 0.01);
            }
            
            draw_model(&(scene->cats[i].model));
            glPopMatrix();
        }

        glPushMatrix();
        glTranslatef(scene->bus.position.x, scene->bus.position.y, scene->bus.position.z);
        glRotatef(scene->bus.rotation, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, scene->bus.texture);
        draw_model(&(scene->bus.model));
        glPopMatrix();

        scene->cursor_location = Calculate3DCursorLocation(x, y);

        //pont kiiratás
        char str[10];
        sprintf(str, "%d", scene->score);
        drawText(20, 70, 0.5, 3, GLUT_STROKE_ROMAN, str, 0.85882352941, 0.43921568627, 0.57647058823);

        if(scene->is_over == true){
            sprintf(str, "GAME OVER");
            drawText(80, 400, 1.4, 10, GLUT_STROKE_ROMAN, str, 1, 0, 0);
        }

    } 
    else if(scene->is_start == true){
        drawMenu(scene->game_start);
    } else if(scene->is_over == true){
        drawMenu(scene->game_over);
        char str[3];
        sprintf(str, "%d", scene->score);
        int text_x;
        if(scene->score >= 10 && scene->score < 100){
            text_x = 530;
        } else if(scene->score < 10){
            text_x = 580;
        } else if(scene->score >= 100){
            text_x = 480;
        }
        drawText(text_x, 470, 1.4, 10, GLUT_STROKE_ROMAN, str, 1, 1, 1);
    }
        
}

void get_elapsed_time(Scene* scene)
{
    uint32_t current_time = SDL_GetTicks();
    uint32_t new_elapsed_time = current_time - scene->base_time;
    if(new_elapsed_time >= 1){
        scene->elapsed_time = new_elapsed_time;
        scene->base_time = current_time;
    }
    else{
        scene->elapsed_time = 0;
    }
}

void grab_the_cat(Scene* scene)
{
    for(int i=0; i<MAX_CATS; i++){
        if(get_distance(scene->cursor_location.x, scene->cats[i].position.x , scene->cursor_location.y, scene->cats[i].position.y) < 0.25){
            scene->cats[i].is_grabbed = true;
            break;
        }
    }   
}

void release_cat(Scene* scene)
{
    for(int i=0; i<MAX_CATS; i++){
        scene->cats[i].is_grabbed = false;
    }
}