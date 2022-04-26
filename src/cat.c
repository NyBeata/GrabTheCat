#include "cat.h"
#include <stdio.h>

void cat_ai_handler(Cat* cat, int elapsed_time)
{
    cat->decision_time = cat->decision_time - elapsed_time;
    printf("\n%d", elapsed_time);
    if(cat->decision_time < 100){
        cat->speed = (rand() %(1 - 0 + 1)) + 0;
        cat->rotation = (rand() %(90 - (-90) + 1)) + (-90);
        cat->decision_time = (rand() %(5000 - 1000 + 1)) + 1000;

        printf("\nTHE CAT HAS DECIDED. IT WILL DECIDE AGAIN IN %d MILISECS", cat->decision_time);
    }


        
       // printf("\nIT WILL DECIDE AGAIN IN %d MILISECS", cat->decision_time);
    
}