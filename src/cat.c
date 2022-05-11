#include "cat.h"
#include <stdio.h>

void cat_ai_handler(Cat* cat, uint32_t elapsed_time)
{
    cat->decision_time = cat->decision_time - elapsed_time;
    if(cat->decision_time < 100){
        cat->speed = ((rand() %(32 - 10 + 1)) + 10) * 0.000028;
        float distance = cat->position.x * 0.5;

        // ha az út elött van
        if(cat->position.x < ROAD_START){
            if(cat->position.y > 1+distance){
                cat->new_rotation = (rand() %(0 - (-80) + 1)) + (-80);
            } else if (cat->position.y < -1-distance){
              cat->new_rotation = (rand() %(80 - 0 + 1)) + 0;
            } else {
             cat->new_rotation = (rand() %(80 - (-80) + 1)) + (-80);
            }

        // ha az úton van
        } else if (cat->position.x >= ROAD_START && cat->position.x < ROAD_END){
            if(cat->position.y > 1+distance){
                cat->new_rotation = (rand() %(0 - (-180) + 1)) + (-180);
            } else if (cat->position.y < -1-distance){
              cat->new_rotation = (rand() %(180 - 0 + 1)) + 0;
            } else {
             cat->new_rotation = (rand() %(180 - (-180) + 1)) + 0;
            }

        //ha túlment az úton
        } else if (cat->position.x >= ROAD_END){
             if(cat->position.y > 1+distance){
                cat->new_rotation = (rand() %((-100) - (-180) + 1)) + (-180);
            } else if (cat->position.y < -1-distance){
              cat->new_rotation = (rand() %((-180) - (-270) + 1)) + (-270);
            } else {
             cat->new_rotation = (rand() %((-100) - (-270) + 1)) + (-270);
            }
        }

        cat->decision_time = (rand() %(4000 - 1000 + 1)) + 1000;
    }
}

void move_cat(Cat* cat, uint32_t elapsed_time)
{
    if(cat->rotation == cat->new_rotation){
        // cica mozgás sebesség és irány alapján
        cat->position.x += cat->speed * cos(degree_to_radian(cat->rotation)) * elapsed_time;
        cat->position.y += cat->speed * sin(degree_to_radian(cat->rotation)) * elapsed_time;
    } else if (cat->rotation > cat->new_rotation){
        // forgás erre
        cat->rotation -= elapsed_time*0.2;
        if(cat->rotation < cat->new_rotation){
            cat->rotation = cat->new_rotation;
        }
    } else if (cat->rotation < cat->new_rotation){
        // forgás arra
        cat->rotation += elapsed_time*0.2;
        if(cat->rotation > cat->new_rotation){
            cat->rotation = cat->new_rotation;
        }
    } 

    // macska megállítása az út végén
    if(cat->position.x > ROAD_END){
        cat->position.x = ROAD_END;
    }
    
}

void relocate_cat(Cat* cat, float x, float y)
{
    cat->position.x = x;
    cat->position.y = y;
}

void spawn_point_generator(Cat* cat)
{
    float y = ((rand() %(10 - (-10) + 1)) + (-10)) * 0.1;
    float x = ((rand() %(0 - (-10) + 1)) + (-10)) * 0.1;
    cat->position.x = x;
    cat->position.y = y;
}

void init_cat(Cat* cat)
{
    load_model(&(cat->model), "assets/models/cat.obj");
    cat->texture = load_texture("assets/textures/cat.jpg");
    spawn_point_generator(cat);
    cat->position.z = -0.28;
    cat->rotation = 0;
    cat->decision_time = 0;
    cat->speed = 0;

    cat->is_grabbed = false;
    cat->is_dead = false;
}

