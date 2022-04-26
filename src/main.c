#include "app.h"


#include <stdio.h>



/**
 * Main function
 */
int main(int argc, char* argv[])
{
    App app;

    init_app(&app, 800, 600);
    while (app.is_running) {
        handle_app_events(&app);
        update_app(&app);
        render_app(&app);
        get_elapsed_time(&(app.scene));
    
    }
    destroy_app(&app);

    return 0;
}

