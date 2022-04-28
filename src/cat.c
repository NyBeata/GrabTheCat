#include "cat.h"
#include <stdio.h>

void cat_ai_handler(Cat* cat, uint32_t elapsed_time)
{
    cat->decision_time = cat->decision_time - elapsed_time;
    printf("\nCAT DECISION TIME: %d", cat->decision_time);
    //printf("\nCAT GOT: %d", elapsed_time);
    if(cat->decision_time < 100){
        cat->speed = ((rand() %(7 - 0 + 1)) + 0) * 0.001;
        cat->new_rotation = (rand() %(90 - (-90) + 1)) + (-90);
        cat->decision_time = (rand() %(5000 - 1000 + 1)) + 1000;

        printf("\nTHE CAT HAS DECIDED. IT WILL DECIDE AGAIN IN %d MILISECS", cat->decision_time);
    }


        
       // printf("\nIT WILL DECIDE AGAIN IN %d MILISECS", cat->decision_time);
    
}

void move_cat(Cat* cat, uint32_t elapsed_time)
{
    if(cat->rotation == cat->new_rotation){
        cat->position.x += cat->speed * cos(degree_to_radian(cat->rotation));
        cat->position.y += cat->speed * sin(degree_to_radian(cat->rotation));
    } else if (cat->rotation > cat->new_rotation){
        cat->rotation -= elapsed_time*0.1;
        if(cat->rotation < cat->new_rotation){
            cat->rotation = cat->new_rotation;
        }
    } else if (cat->rotation < cat->new_rotation){
        cat->rotation += elapsed_time*0.1;
        if(cat->rotation > cat->new_rotation){
            cat->rotation = cat->new_rotation;
        }
    } 
    
}