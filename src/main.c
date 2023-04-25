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
#include "../include/game.h"


int quit = 0;   
Settings* settings;
void sigint_handler(int sig) {
    quit = 1;
}

int temporize(struct timespec  *update_time, unsigned int space_time) {
    struct timespec  current_time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &current_time);
    printf("%ld\n", current_time.tv_nsec/1000000 - update_time->tv_nsec/1000000);

    if(current_time.tv_nsec/1000000 - update_time->tv_nsec/1000000 > space_time) {
        clock_gettime(CLOCK_MONOTONIC_RAW, update_time);
        return 1;
    }

    return 0;
}

int main() {
    Game *game;
    struct timespec update_time, draw_time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &update_time);
    clock_gettime(CLOCK_MONOTONIC_RAW, &draw_time);

    
    signal(SIGINT, sigint_handler);
    srand(time(NULL));
    
    load_settings(settings);
    init_frame();
    game = init_game();
    
    while(!quit) {
        if(temporize(&update_time, 12)) {
            update_game(game); 
        }

        if(temporize(&draw_time, 12)) {
            MLV_clear_window(MLV_COLOR_BLACK);
            draw_frame(game); 
            MLV_actualise_window();
        }
    }

    free_game(game);
    free_frame();
    free(settings);

    return EXIT_SUCCESS;
}