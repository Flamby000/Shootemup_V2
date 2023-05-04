#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <signal.h>
#include <unistd.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/frame.h"
#include "../include/settings.h"
#include "../include/animation.h"
#include "../include/entity.h"
#include "../include/utils.h"
#include "../include/game.h"

int quit = 0;   
Settings* settings;
void sigint_handler(int sig) {
    quit = 1;
}

int main() {
    Game *game;
    long update_time = get_timestamp_ms();
    
    signal(SIGINT, sigint_handler);
    srand(time(NULL));
    
    load_settings(settings);
    init_frame();
    
    game = init_game();

    while(!quit) {
        if(temporize(&update_time, 12)) continue;

        update_game(game);

        MLV_clear_window(MLV_COLOR_BLACK);
        draw_frame(game); 
        MLV_actualise_window();
    }

    free_game(game);
    free_frame();
    free(settings);

    return EXIT_SUCCESS;
}