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


int main() {
    struct timespec start_frame_time;
    struct timespec end_frame_time;
    int frame_time;
    Game *game;
    
    signal(SIGINT, sigint_handler);
    srand(time(NULL));
    
    load_settings(settings);
    init_frame();
    game = init_game();
    
    
    while(!quit) {
        clock_gettime(CLOCK_MONOTONIC, &start_frame_time);
        MLV_clear_window(MLV_COLOR_BLACK);

        update_frame(game);
        update_game(game);

        clock_gettime(CLOCK_MONOTONIC, &end_frame_time);
        frame_time = (end_frame_time.tv_sec - start_frame_time.tv_sec) + (end_frame_time.tv_nsec - start_frame_time.tv_nsec) / 1000000000.0;
        if(frame_time < (1.0/GAME_SPEED)) {
            MLV_wait_milliseconds((int)(((1.0/GAME_SPEED) - frame_time) * 1000));
        }
        MLV_actualise_window();

    }

    free_game(game);
    free_frame();
    free(settings);
    

    return EXIT_SUCCESS;
}